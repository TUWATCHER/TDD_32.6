#pragma once

#include <string>

class IDBConnection
{
    public:
        IDBConnection() {}
        virtual ~IDBConnection() {}
        virtual bool open(std::string hostname) = 0;
        virtual bool close_c() = 0;
        virtual bool execQuery(std::string query) = 0;
};

class DBConnection : public IDBConnection
{
    public:
        ~DBConnection() { close_c(); }
        bool open(std::string hostname) override
        {
            if(!isOpen)
            {
                isOpen = true;
                return true;
            }
            else return false;
            
        }
        bool close_c() override
        {
            if(isOpen)
            {
                isOpen = false;
                return true;
            }
            else return false;
        }
        bool execQuery(std::string query) override
        {
            if (query.empty()) return false;
            else return true;
        }
    private:
        bool isOpen = false;
        
};

class ClassThatUsesDB
{
    public:
        
        bool openConnection(IDBConnection& object)
        {
            return object.open("localhost");
        }
        bool closeConnection(IDBConnection& object)
        {
            return object.close_c();
        }
        bool useConnection(IDBConnection& object,std::string _query)
        {
            return object.execQuery(_query);
        }    
};