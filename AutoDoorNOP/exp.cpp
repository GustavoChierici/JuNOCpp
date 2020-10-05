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
        Premise* prPersonInDoorFront = new Premise("EQUAL");
        prPersonInDoorFront->setAttribute(person->at_pos_door_front, true);

        Premise* prIsDoorOpen = new Premise();
        prIsDoorOpen->setAttribute(door->at_is_open, true);

        Premise* prIsPersonMoving = new Premise(">");
        prIsPersonMoving->setAttribute(person->at_velocity, 0.0);

        //Init Rules
        Rule* rlOpenDoor = new Rule("CONJUNCTION", Rule::COMPLETE);
        rlOpenDoor->addPremise(prPersonInDoorFront);
        rlOpenDoor->addPremise(prIsPersonMoving);
        rlOpenDoor->addPremise(door->at_is_open, false, "==");
        rlOpenDoor->addPremise(sensor->at_person_detected, true, "EQUAL");    
        rlOpenDoor->addInstigation(door->at_is_open, true);
        //rlOpenDoor->referenceAttr(door->at_is_open, true);
        //rlOpenDoor->setCustomExecution([](Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
        //     std::cout << "(NOP) Abrindo porta..." << std::endl;
        //     static_cast<Boolean*>(attr)->setStatus(true);
        // });   

        Rule* rlPersonPassDoor = new Rule("CONJUNCTION");
        rlPersonPassDoor->addPremise(prPersonInDoorFront);
        rlPersonPassDoor->addPremise(prIsDoorOpen);
        rlPersonPassDoor->addPremise(prIsPersonMoving);
        rlPersonPassDoor->addInstigation(person->at_pos_door_front, false);
        //rlPersonPassDoor->referenceAttr(person->at_pos_door_front, false);
        // rlPersonPassDoor->setCustomExecution([](Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
        //     std::cout << "(NOP) Pessoa passando..." << std::endl;
        //     static_cast<Boolean*>(attr)->setStatus(false);
        // });

        Rule* rlCloseDoor = new Rule();
        rlCloseDoor->addPremise(person->at_pos_door_front, false);
        rlCloseDoor->addPremise(prIsDoorOpen);
        rlCloseDoor->addPremise(sensor->at_person_detected, false);
        //rlCloseDoor->referenceAttr(door->at_is_open, false);
        rlCloseDoor->addInstigation(door->at_is_open, false);
        // rlCloseDoor->setCustomExecution([](Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
        //     std::cout << "(NOP) Fechando porta..." << std::endl;
        //     static_cast<Boolean*>(attr)->setStatus(false);
        // });

        //Init initial Attributes status

        person->at_pos_door_front->setStatus(false);
        person->at_velocity->setStatus(1.5);

        sensor->at_person_detected->setStatus(false);

        door->at_is_open->setStatus(false);
        

        NOPpersons.push_back(person);
        NOPdoors.push_back(door);
        NOPsensors.push_back(sensor);
    }

    start = clock();

    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < ((percentage/100) * elements); j++)
        {
            NOPpersons.at(j)->at_pos_door_front->setStatus(true);
            NOPsensors.at(j)->at_person_detected->setStatus(true);
            NOPsensors.at(j)->at_person_detected->setStatus(false);
        }
    }
    finish = clock();

    std::cout << "O tempo total do JuNOC++ foi de: " << finish - start << " ms - Regras aprovadas: "<< Rule::counter << std::endl;

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

    std::cout << "O tempo total do PI foi de: " << finish - start << " ms - Regras aprovadas: " << counter << std::endl;

    for(int i = 0; i < elements; i++)
    {
        //Init FBEs
        NOPPerson* person = new NOPPerson();
        NOPDoor* door = new NOPDoor();
        NOPSensor* sensor = new NOPSensor();

        //Init shared Premises
        Premise* prPersonInDoorFront = new Premise("EQUAL");
        prPersonInDoorFront->setAttribute(person->at_pos_door_front, true);

        Premise* prIsDoorOpen = new Premise();
        prIsDoorOpen->setAttribute(door->at_is_open, true);

        Premise* prIsPersonMoving = new Premise(">");
        prIsPersonMoving->setAttribute(person->at_velocity, 0.0);

        //Init Rules
        Rule* rlOpenDoor = new Rule("CONJUNCTION", Rule::COMPLETE);
        rlOpenDoor->addPremise(prPersonInDoorFront);
        rlOpenDoor->addPremise(prIsPersonMoving);
        rlOpenDoor->addPremise(door->at_is_open, false, "==");
        rlOpenDoor->addPremise(sensor->at_person_detected, true, "EQUAL");
        //rlOpenDoor->referenceAttr(door->at_is_open, true);
        rlOpenDoor->addInstigation(door->at_is_open, true);
        rlOpenDoor->addInstigation(person->at_pos_door_front, false);
        rlOpenDoor->addInstigation(sensor->at_person_detected, false);
        rlOpenDoor->addInstigation(door->at_is_open, false);

        // Rule* rlPersonPassDoor = new Rule("CONJUNCTION", Rule::COMPLETE);
        // rlPersonPassDoor->addPremise(prPersonInDoorFront);
        // rlPersonPassDoor->addPremise(prIsDoorOpen);
        // rlPersonPassDoor->addPremise(prIsPersonMoving);
        // //rlPersonPassDoor->referenceAttr(person->at_pos_door_front, false);
        // rlPersonPassDoor->referenceAttr(person->at_pos_door_front, false);

        // Rule* rlCloseDoor = new Rule("CONJUNCTION", Rule::COMPLETE);
        // rlCloseDoor->addPremise(person->at_pos_door_front, false);
        // rlCloseDoor->addPremise(prIsDoorOpen);
        // rlCloseDoor->addPremise(sensor->at_person_detected, false);
        // //rlCloseDoor->referenceAttr(door->at_is_open, false);
        // rlCloseDoor->addInstigation(door->at_is_open, false);

        //Init initial Attributes status

        person->at_pos_door_front->setStatus(false);
        person->at_velocity->setStatus(1.5);

        sensor->at_person_detected->setStatus(false);

        door->at_is_open->setStatus(false);
        

        NOPpersons.push_back(person);
        NOPdoors.push_back(door);
        NOPsensors.push_back(sensor);
    }

    Rule::counter = 0;
    start = clock();

    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < ((percentage/100) * elements); j++)
        {
            NOPpersons.at(j)->at_pos_door_front->setStatus(true);
            NOPsensors.at(j)->at_person_detected->setStatus(true);
            // NOPsensors.at(j)->at_person_detected->setStatus(false);
        }
    }
    finish = clock();

    std::cout << "O tempo total do JuNOC++ em uma unica regra foi de: " << finish - start << " ms - Regras aprovadas: " << Rule::counter << std::endl;

    return 0;
}
