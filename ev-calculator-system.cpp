#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

class EVCalculator {
private:
    // Basic EV specifications
    double batteryCapacity;    // in kWh
    double efficiency;         // in kWh/100km
    double chargingPower;      // in kW
    double currentCharge;      // in percentage
    double electricityRate;    // per kWh

public:
    EVCalculator() {
        batteryCapacity = 0;
        efficiency = 0;
        chargingPower = 0;
        currentCharge = 0;
        electricityRate = 0;
    }

    // Setter methods
    void setBatterySpecs(double capacity, double eff) {
        batteryCapacity = capacity;
        efficiency = eff;
    }

    void setChargingSpecs(double power, double rate) {
        chargingPower = power;
        electricityRate = rate;
    }

    void setCurrentCharge(double charge) {
        currentCharge = charge;
    }

    // Calculate remaining range
    double calculateRange() {
        double usableCapacity = batteryCapacity * (currentCharge / 100.0);
        return (usableCapacity / efficiency) * 100;  // Convert to km
    }

    // Calculate charging time from current to full
    double calculateChargingTime() {
        double remainingCapacity = batteryCapacity * (1 - currentCharge / 100.0);
        return (remainingCapacity / chargingPower) * 60;  // Convert to minutes
    }

    // Calculate charging cost from current to full
    double calculateChargingCost() {
        double remainingCapacity = batteryCapacity * (1 - currentCharge / 100.0);
        return remainingCapacity * electricityRate;
    }

    // Calculate carbon offset compared to gas vehicle
    double calculateCarbonOffset(double distance) {
        // Average gas car emits 2.31 kg CO2 per liter
        // Average gas car uses 8.9 L/100km
        double gasEmissions = (distance / 100) * 8.9 * 2.31;
        
        // EV emissions based on electricity generation (varies by region)
        // Using average of 0.5 kg CO2 per kWh
        double evEmissions = (distance / 100) * efficiency * 0.5;
        
        return gasEmissions - evEmissions;  // kg of CO2 saved
    }
};

class EVAnalysisSystem {
private:
    EVCalculator calculator;
    
public:
    void run() {
        int choice;
        setupEV();
        
        do {
            displayMenu();
            std::cin >> choice;
            
            switch(choice) {
                case 1:
                    calculateRangeAndDisplay();
                    break;
                case 2:
                    calculateChargingMetrics();
                    break;
                case 3:
                    calculateEnvironmentalImpact();
                    break;
                case 4:
                    updateEVSpecs();
                    break;
                case 0:
                    std::cout << "Exiting program...\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }

private:
    void displayMenu() {
        std::cout << "\nEV Analysis System\n";
        std::cout << "1. Calculate Remaining Range\n";
        std::cout << "2. Charging Analysis\n";
        std::cout << "3. Environmental Impact Analysis\n";
        std::cout << "4. Update EV Specifications\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
    }

    void setupEV() {
        double capacity, efficiency, power, rate;
        
        std::cout << "Enter EV Specifications:\n";
        std::cout << "Battery Capacity (kWh): ";
        std::cin >> capacity;
        std::cout << "Efficiency (kWh/100km): ";
        std::cin >> efficiency;
        std::cout << "Charging Power (kW): ";
        std::cin >> power;
        std::cout << "Electricity Rate (per kWh): ";
        std::cin >> rate;
        
        calculator.setBatterySpecs(capacity, efficiency);
        calculator.setChargingSpecs(power, rate);
    }

    void calculateRangeAndDisplay() {
        double currentCharge;
        std::cout << "Enter current battery charge (%): ";
        std::cin >> currentCharge;
        calculator.setCurrentCharge(currentCharge);
        
        double range = calculator.calculateRange();
        std::cout << "Estimated remaining range: " << std::fixed 
                  << std::setprecision(2) << range << " km\n";
    }

    void calculateChargingMetrics() {
        double currentCharge;
        std::cout << "Enter current battery charge (%): ";
        std::cin >> currentCharge;
        calculator.setCurrentCharge(currentCharge);
        
        double time = calculator.calculateChargingTime();
        double cost = calculator.calculateChargingCost();
        
        std::cout << "Charging time to full: " << std::fixed 
                  << std::setprecision(1) << time << " minutes\n";
        std::cout << "Charging cost to full: $" << std::fixed 
                  << std::setprecision(2) << cost << "\n";
    }

    void calculateEnvironmentalImpact() {
        double distance;
        std::cout << "Enter distance traveled (km): ";
        std::cin >> distance;
        
        double carbonSaved = calculator.calculateCarbonOffset(distance);
        std::cout << "Carbon emissions saved: " << std::fixed 
                  << std::setprecision(2) << carbonSaved << " kg CO2\n";
    }

    void updateEVSpecs() {
        setupEV();
        std::cout << "EV specifications updated successfully!\n";
    }
};

int main() {
    EVAnalysisSystem system;
    system.run();
    return 0;
}
