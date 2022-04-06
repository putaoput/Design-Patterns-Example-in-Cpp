#include <set>
#include <iostream>

class ObserverInterface{
 public:
    virtual void Update(float temp, float humidity, float pressure) = 0;
};

class SubjectInterface{
 public:
    virtual void RegisterObserver(ObserverInterface* o) = 0;
    virtual void RemoveObserver(ObserverInterface* o) = 0;
    virtual void NotifyObservers() = 0;

};

class DisplayElementInterface{
 public:
   virtual void Display() = 0;
};


class WeatherData:public SubjectInterface{
 public:
    WeatherData() = default;
    void RegisterObserver(ObserverInterface* o){
        observers_.insert(o);
    }
    void RemoveObserver(ObserverInterface* o){
        if(observers_.count(o)){
            observers_.erase(o);
        }
    }
    void NotifyObservers(){
        for(auto observer:observers_){
            observer->Update(temperature_, humidity_, pressure_);
        }
    }
    void MeasurementsChanged(){
        NotifyObservers();
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

class CurrentConditionsDisplay: 
    public ObserverInterface,
    public DisplayElementInterface{
 public:
    CurrentConditionsDisplay(SubjectInterface* weather_data){
        weather_data_ = weather_data;
        weather_data_->RegisterObserver(this);
    }

    void Update(float temperature, float humidity, float pressure){
        temperature_ = temperature;
        humidity_ = humidity;
        Display();
    }

    void Display(){
        std::cout << "Current conditions: " << temperature_ << "F degrees and " << humidity_ << "% humidity" << std::endl;
    }
 private:
    float temperature_;
    float humidity_;
    SubjectInterface* weather_data_;
};

void TestObserver(){
    WeatherData* weather_data = new WeatherData();

    CurrentConditionsDisplay* current_conditions_display = new CurrentConditionsDisplay(weather_data); 
    
    weather_data->SetMeasurements(80, 65, 30.4f);
    weather_data->SetMeasurements(82, 70, 29.2f);
    weather_data->SetMeasurements(78, 90, 29.2f);
}