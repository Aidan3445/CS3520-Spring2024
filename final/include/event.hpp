#ifndef EVENT_HPP
#define EVENT_HPP

#include "dateTime.hpp"
#include "user.hpp"

enum LayoutStyle {
    MEETING, LECTURE, WEDDING, DANCE
};

class Event {
    private:
        // Start time also acts as an ID for this Event
        DateTime startTime, endTime;
        LayoutStyle style;
        std::string organizerID;

    public:
        Event(DateTime startTime, DateTime endTime, LayoutStyle style);
        /** Getters */
        DateTime getStartTime() const;
        DateTime getEndTime() const;
        std::string getOrganizerID() const;
        LayoutStyle getStyle() const;
};

class PublicEvent : public Event {
    private:
        std::vector<std::string> guestList;
        bool openToNonResidents;

    public:
        PublicEvent(DateTime startTime, DateTime endTime, LayoutStyle style, bool openToNonResidents = true);
        /** Adds a ticket to this event to the given user */
        void purchaseTicket(User user);
};

typedef Event PrivateEvent;

#endif