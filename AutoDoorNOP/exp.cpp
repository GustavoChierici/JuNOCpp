#include "NOPPerson.hpp"
#include "NOPDoor.hpp"
#include "NOPSensor.hpp"
#include <vector>
#include <ctime>
#include "Person.hpp"
#include "Door.hpp"
#include "Sensor.hpp"

int main()
{
    std::vector<NOPPerson*> NOPpersons;
    std::vector<NOPDoor*> NOPdoors;
    std::vector<NOPSensor*> NOPsensors;

    long iterations = 0, elements = 0;;
    double start, finish;
    float percentage = 0;

    std::cout << "Quantidade de elementos: ";
    std::cin >> elements;
    std::cout << "Quantidade de iteracoes: ";
    std::cin >> iterations;
    std::cout << "Porcentagem de pessoas detectadas: ";
    std::cin >> percentage;

    for(int i = 0; i < elements; i++)
    {
        //Init FBEs
        NOPPerson* person = new NOPPerson();
        NOPDoor* door = new NOPDoor();
        NOPSensor* sensor = new NOPSensor();

        //Init shared Premises
        NOP::PremiseEqual<bool, bool> prPersonOnDoorFront = person->at_pos_door_front == true;
        NOP::PremiseEqual<bool, bool> prIsDoorOpen = door->at_is_open == true;
        NOP::PremiseGreaterEqual<double, double> prIsPersonMoving = person->at_velocity >= 0.0;

        //Init Rules
        RULE(prPersonOnDoorFront and prIsPersonMoving and door->at_is_open == false and sensor->at_person_detected == true)
            INSTIGATE([=](){door->at_is_open = true;})
        END_RULE

        door->at_is_open.setStatus(false, true);

        RULE(prPersonOnDoorFront and prIsDoorOpen and prIsPersonMoving)
            INSTIGATE([=](){person->at_pos_door_front = false;})
            INSTIGATE([=](){sensor->at_person_detected = false;})
        END_RULE

        RULE(person->at_pos_door_front == false and prIsDoorOpen and sensor->at_person_detected == false)
            INSTIGATE([=](){door->at_is_open = false;})
        END_RULE

        //Init Attributes status

        person->at_pos_door_front = false;
        person->at_velocity = 1.5;

        sensor->at_person_detected = false;

        NOPpersons.push_back(person);
        NOPdoors.push_back(door);
        NOPsensors.push_back(sensor);
    }

    start = clock();

    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < ((percentage/100) * elements); j++)
        {
            NOPpersons.at(j)->at_pos_door_front = true;
            NOPsensors.at(j)->at_person_detected = true;
        }
    }
    finish = clock();

    std::cout << "O tempo total do JuNOC++ foi de: " << (finish - start)/CLOCKS_PER_SEC << " s - Regras aprovadas: "<< Core::Rule::approved << std::endl;

    NOPdoors.clear();
    NOPsensors.clear();
    NOPpersons.clear();

    std::vector<Person*> persons;
    std::vector<Door*> doors;
    std::vector<Sensor*> sensors;

    for(int i = 0; i < elements; i++)
    {
        Person* person = new Person();
        person->pos_door_front = false;
        person->velocity = 1.5;
        persons.push_back(person);

        Door* door = new Door();
        door->is_open = false;
        doors.push_back(door);

        Sensor* sensor = new Sensor();
        sensor->person_detected = false;
        sensors.push_back(sensor);
    }

    start = clock();
    
    long int counter = 0;
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < ((percentage/100) * elements); j++)
        {
            persons.at(j)->pos_door_front = true;
            sensors.at(j)->person_detected = true;
        }

        for(int j = 0; j < elements; j++)
        {
            if(doors.at(j)->is_open == false && persons.at(j)->velocity > 0.0 && persons.at(j)->pos_door_front == true && sensors.at(j)->person_detected == true)
            {
                //std::cout << "Abrindo porta..." << std::endl;
                doors.at(j)->is_open = true;
                counter++;
            }
            if(persons.at(j)->velocity > 0.0 && persons.at(j)->pos_door_front == true and doors.at(j)->is_open == true)
            {
                //std::cout << "Pessoa passando..." << std::endl;
                persons.at(j)->pos_door_front = false;
                sensors.at(j)->person_detected = false;
                counter++;
            }
            if(sensors.at(j)->person_detected == false && persons.at(j)->pos_door_front == false && doors.at(j)->is_open == true)
            {
                //std::cout << "Fechando porta..." << std::endl;
                doors.at(j)->is_open = false;
                counter++;
            }
        }
    }

    finish = clock();

    std::cout << "O tempo total do PI foi de: " << (finish - start)/CLOCKS_PER_SEC << " s - Regras aprovadas: " << counter << std::endl;

    for(int i = 0; i < elements; i++)
    {
        //Init FBEs
        NOPPerson* person = new NOPPerson();
        NOPDoor* door = new NOPDoor();
        NOPSensor* sensor = new NOPSensor();

        //Init shared Premises
        NOP::PremiseEqual<bool, bool> prPersonOnDoorFront = person->at_pos_door_front == true;

        NOP::PremiseEqual<bool, bool> prIsDoorOpen = door->at_is_open == true;

        NOP::PremiseGreaterEqual<double, double> prIsPersonMoving = person->at_velocity >= 0.0;
        
        RULE(person->at_pos_door_front == true)
            INSTIGATE([](){std::cout << "It works!" << std::endl; })
        END_RULE

        //Init Rules
        RULE(prPersonOnDoorFront and prIsPersonMoving and (door->at_is_open == false and sensor->at_person_detected == true))
            INSTIGATE([=](){door->at_is_open = true;})
            INSTIGATE([=](){person->at_pos_door_front = false;})
            INSTIGATE([=](){sensor->at_person_detected = false;})
            INSTIGATE([=](){door->at_is_open = false;})
        END_RULE

        person->at_pos_door_front = false;
        person->at_velocity = 1.5;

        sensor->at_person_detected = false;

        door->at_is_open.setStatus(false, true);

        NOPpersons.push_back(person);
        NOPdoors.push_back(door);
        NOPsensors.push_back(sensor);
    }

    Core::Rule::approved = 0;
    start = clock();

    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < ((percentage/100) * elements); j++)
        {
            NOPpersons.at(j)->at_pos_door_front = true;
            NOPsensors.at(j)->at_person_detected = true;
        }
    }
    finish = clock();

    std::cout << "O tempo total do JuNOC++ em uma unica regra foi de: " << (finish - start)/CLOCKS_PER_SEC << " s - Regras aprovadas: " << Core::Rule::approved << std::endl;

    return 0;
}
