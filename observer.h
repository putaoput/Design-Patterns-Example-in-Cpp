#include <set>


class ObserverInterface{
 public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class SubjectInterface{
 public:
    virtual void registerObserver(ObserverInterface* o) = 0;
    virtual void removeObserver(ObserverInterface* o) = 0;
    virtual void notifyObservers() = 0;

};

class DisplayElementInterface{
 public:
    void display();
};


class WeatherData:public SubjectInterface{
 public:
    WeatherData() = default;
    void registerObserver(ObserverInterface* o){
        observers_.insert(o);
    }
    void RemoveObserver(ObserverInterface* o){
        if(observers_.count(o)){
            observers_.erase(o);
        }
    }
    void NotifyObservers(){
        for(auto observer:observers_){
            observer->update(temperature_, humidity_, pressure_);
        }
    }
    void MeasurementsChanged(){
        notifyObservers();
    }
    void SetMeasurements(float temperature, float humidity, float pressure){
        temperature_ = temperature;
        humidity_ = humidity;
        pressure_ = pressure;
        MeasurementsChanged();
    }
 private:
    std::set<ObserverInterface*> observers_;
    float temperature_;
    float humidity_;
    float pressure_;
};
