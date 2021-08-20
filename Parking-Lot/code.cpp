#include <bits/stdc++.h>
using namespace std;
class ParkingSlot;
class TicketBooth;
class Parking;

enum SlotType {COMPACT, SEDAN, MOTORBIKE};
class ParkingSlot
{
    private :
        SlotType slot_type;
        int id;
        bool isOccupied;
        int duration;
        TicketBooth* nearest_exit;
        string vehical_id;
        string vehical_color;


    public :
        // constructor
        ParkingSlot(int id, SlotType slot_type, TicketBooth* nearest_exit)
        {
            isOccupied = false;
            duration = 0;
            this -> nearest_exit = nearest_exit;
            this -> id = id;
            this -> slot_type = slot_type;
            vehical_color = "";
            vehical_id = "";
        }
        // getters
        SlotType getSlotType()
        {
            return slot_type;
        }
        int getID()
        {
            return id;
        }
        int getDuration()
        {
            return duration;
        }
        bool isFree()
        {
            return !isOccupied;
        }
        TicketBooth* getNearestExit()
        {
            return nearest_exit;
        }
        string getVehicalID()
        {
            return vehical_id;
        }
        string getVehicalColor()
        {
            return vehical_color;
        }

        // setters
        void setDuration(int duration)
        {
            this -> duration = duration;
        }
        void setisFree(bool isFree)
        {
            this -> isOccupied = !isFree;
        }
        void setVehicalID(string vehical_id)
        {
            this -> vehical_id = vehical_id;
        }
        void setVehicalColor(string vehical_color)
        {
            this -> vehical_color = vehical_color;
        }
        void displaySlotInfo()
        {
            cout << "Slot id : " << id << "\n";
            cout << "Slot Status : " << (isOccupied)? "Occupied\n" : "Empty\n";
            cout << "Slot Type : ";
            switch(slot_type)
            {
                case COMPACT: cout << "COMPACT\n";
                            break;
                case SEDAN: cout << "SEDAN\n";
                            break;
                case MOTORBIKE : cout << "MOTORBIKE\n";
                            break;
            }
            if(isOccupied)
            {
                cout << "vehical Registration : " << vehical_id << "\n";
                cout << "Vehical Color : " << vehical_color << "\n";
                cout << "Parking Duration : " << duration << "\n";
            }
        }
};

class TicketBooth
{
    private:
        int id;
        int total_free_slots;
        int free_slots[3];
        vector<ParkingSlot*> parking_slots;

    public:
        // constructor
        TicketBooth(int id, vector<ParkingSlot*> parking_slots)
        {
            for(int i = 0; i<3; i++)
                free_slots[i] = 0;

            this -> id = id;
            this -> parking_slots = parking_slots;
            total_free_slots = parking_slots.size();
            for(auto i : parking_slots)
                free_slots[i -> getSlotType()]++;
        }

        bool isCompactFree()
        {
            return free_slots[0];
        }

        bool isSedanFree()
        {
            return free_slots[1];
        }

        bool isMotorBikeFree()
        {
            return free_slots[2];
        }

        vector<ParkingSlot*> getParkingSlots()
        {
            return parking_slots;
        }

        // getters
        int getID()
        {
            return id;
        }
        void displayAllSlotes()
        {
            for(auto i : parking_slots)
            {
                cout << "==============================\n";
                i -> displaySlotInfo();
                cout << "===============================\n";
            }
        }

        ParkingSlot* addVehical(string vehical_id, string vehical_color, SlotType slot_type, int duration)
        {
            // if no slots available for the car then reject request
            if(!free_slots[slot_type])
                    return NULL;

            // find nearest slot to the exit of the Type
            ParkingSlot* ticket = NULL;
            for(auto i : parking_slots)
            {
                if(i -> getSlotType() == slot_type && i -> isFree())
                {
                    free_slots[slot_type]--;
                    i -> setVehicalID(vehical_id);
                    i -> setVehicalColor(vehical_color);
                    i -> setisFree(false);
                    i -> setDuration(duration);
                    ticket = i;
                    break;
                }
            }
            return ticket;
        }

        // returns extra time in minutes
        int removeVehical(ParkingSlot* ticket, int actual_duration)
        {
            int reserve_duration = ticket -> getDuration();
            int extra_time = (reserve_duration < actual_duration)? actual_duration - reserve_duration : 0;
            ticket -> setVehicalID("");
            ticket -> setVehicalColor("");
            ticket -> setisFree(true);
            ticket -> setDuration(0);

            return extra_time;
        }
};

class Parking
{
    private :
        int rates[3];       // hourly rates
        double total_revenue;
        static int cars_parked;
        int max_cap;
        vector<double> ticket_booth_revenue;
        vector<TicketBooth*> ticket_booths;

    public :
        Parking(vector<vector<ParkingSlot*>> parking, int compact_rate, int saden_rate, int moterbike_rate)
        {
            // parking = 2D matrix ; parking.size() = number of ticketbooths ; each row is array of parkingslots closest to parking[i] ticketbooth.

            for(auto i : parking)
            {
                max_cap += i.size();
                int id = ticket_booths.size();
                TicketBooth* current_ticket_booth = new TicketBooth(id, i);
                ticket_booths.push_back(current_ticket_booth);
                ticket_booth_revenue.push_back(0);
            }
            total_revenue = 0;
            rates[0] = compact_rate;
            rates[1] = saden_rate;
            rates[2] = moterbike_rate;
        }

        // car enters parking lot with any entry
        ParkingSlot* enterParking(string vehical_id, string vehical_color, SlotType slot_type, int duration, int entry = 0)
        {
            // search the parking space of the designated slottype with the least distance from the parking space.
            // level by level. starting from 'entry id'
            if(entry < 0 || entry == ticket_booths.size())
                return NULL;


            TicketBooth* ticket_booth = ticket_booths[entry];
            ParkingSlot* ticket = ticket_booth -> addVehical(vehical_id, vehical_color, slot_type, duration);

            if(!ticket)
            {
                ParkingSlot* search_left = this -> enterParking(vehical_id, vehical_color, slot_type, duration, entry - 1);
                ParkingSlot* search_right = this -> enterParking(vehical_id, vehical_color, slot_type, duration, entry + 1);

                if(!search_left && !search_right)
                    return NULL;

                cars_parked++;
                return (search_left)? search_left : search_right;
            }
            cars_parked++;
            return ticket;
        }

        // car exits and collects the revenue from the parking lot.
        void exitParking(ParkingSlot* ticket, int parking_duration)
        {
            TicketBooth* ticket_booth = ticket -> getNearestExit();
            int park_time = ticket -> getDuration();
            int extra_time = ticket_booth -> removeVehical(ticket, parking_duration);


            double revenue = ((park_time + extra_time) / 60) * rates[ticket -> getSlotType()];
            total_revenue += revenue;
            ticket_booth_revenue[ticket -> getID()] += revenue;
            cars_parked--;
        }

        // returns cars in the parking facility of "car_type"
        vector<ParkingSlot*> searchByType(SlotType car_type)
        {
            vector<ParkingSlot*> cars;
            for(auto ticket_booth : ticket_booths)
            {
                for(auto parking_slot : ticket_booth -> getParkingSlots())
                {
                    if(!parking_slot -> isFree() && parking_slot -> getSlotType() == car_type)
                        cars.push_back(parking_slot);
                }
            }
            return cars;
        }


        // returns cars in the parking facility of "color"
        vector<ParkingSlot*> searchByColor(string color)
        {
            vector<ParkingSlot*> cars;
            for(auto ticket_booth : ticket_booths)
            {
                for(auto parking_slot : ticket_booth -> getParkingSlots())
                {
                    if(!parking_slot -> isFree() && parking_slot -> getVehicalColor() == color)
                        cars.push_back(parking_slot);
                }
            }
            return cars;
        }

};
int main()
{
    // input number of exits
    // build parking slot array for each ticket booth and store it in a 2D array
    // pass the 2D array into the Parking class.

    return 0;
}
