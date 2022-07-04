#include <iostream>
#include <random>
#include "TrafficLight.h"
#include<algorithm>


/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
	std::unique_lock<std::mutex> u_lck(_mtx);
	_cond.wait(u_lck,[this]{return !_queue.empty();});
     TrafficLightPhase t = std::move(_queue.front());
    _queue.pop_back();
	return t;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
	std::lock_guard<std::mutex> _lck(_mtx);
	_queue.push_back(std::move(msg));
	
	_cond.notify_one();
}


/* Implementation of class "TrafficLight" */
 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while(true)
    {
		
		if(TrafficLightPhase::green == TrafficLight::_messages.receive())
        {
			return ;



        }




    }
	
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
	threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
	/*std::chrono::time_point<std::chrono::system_clock> lastUpdate;
	lastUpdate = std::chrono::system_clock::now();
	double timeSinceLastUpdate = 0.0; */
	/*std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(4000, 6000);
	auto cycleDuration = uni(rng); */

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(4.0, 6.0);
    float cycleTime = dist(mt);

	auto lastUpdate  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeSinceLastUpdate;

	while(true)
    {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		timeSinceLastUpdate = std::chrono::high_resolution_clock::now() - lastUpdate; 
		/*timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
	    timeSinceLastUpdate /= 1000; */
		/*std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(4000, 6000);
		auto cycleDuration = uni(rng); */
		//std::cout << timeSinceLastUpdate << std::endl; 
		if(timeSinceLastUpdate.count() > cycleTime)
        {
			//std::cout << "inside" << std::endl;
			cycleTime = dist(mt);
			lastUpdate = std::chrono::high_resolution_clock::now();
			//timeSinceLastUpdate = 0.0;

			if(TrafficLight::getCurrentPhase() == TrafficLightPhase::red)
            {
				TrafficLight::_currentPhase = TrafficLightPhase::green;
            }
			else
            {
				TrafficLight::_currentPhase = TrafficLightPhase::red;
            }
			_messages.send(std::move(TrafficLight::_currentPhase));
			
        }
		

		
    }
	return;;


}

