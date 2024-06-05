The project is a simulation for a drone delivery system across the University of Minnesota - Twin Cities campus. Within this system, deliveries can be scheduled across the map of the campus and these deliveries are scheduled individually between two location points using a specific search strategy. After the delivery is scheduled, the drone will move towards picking up the package and delivering it to a desired destination to a Robot entity waiting to receive the package. The drone delivery simulation system also consists of other entities like Humans and a Helicopter which enhances the realisticness of the simulation. 

The drone delivery system provides the ability to action replay by creating and loading restore points manually allowing backtracking within the simulation. Moreover, the simulation allows for restoring to the start of the simulation state. Additionally, the simulation collects data on deliveries that are scheduled over the course of the simulation which provides an in-depth analytical analysis of entity movements throughout the simulation aiding in establishing a business perspective for the simulation. 


Running the simulation locally

To run the simulation on your local machine, it is essential to be in the correct directory therefore,

cd go/to/project/folder

Now in the project folder, we need to build the project so,

make -j 

After this was successful, we need to run the project using, 

make run 

The simulation is mainly responsible for demonstrating the scenario of a drone delivery system to primarily highlight the interaction between various entities present and their interaction with one another. The simulation upon starting displays the map and a dashboard that allows users to schedule deliveries between two locations. By selecting the 'Schedule Trip’ option and entering a delivery name, the user can specify the pickup and dropoff locations by clicking on the corresponding areas on the simulation map. Based on the locations chosen, the drone begins to collect the package from the pickup point and then navigates to the dropoff location. The process of navigation takes place twice with the help of the search strategy in order to first locate the pickup point and then travel from the pickup to the dropoff location where there is an additional option for the user to select a particular search strategy for the drone to follow in the process of delivering the package. At the dropoff location, a robot is stationed to receive the package from the drone, ensuring the delivery is completed successfully.

In addition to this, the simulation includes options to add more drones which further creates more drone entities responsible for handling multiple deliveries being scheduled at various locations of the map. Similarly, there is a feature option to add humans into the simulation to show the simulation's realisticness and showcase more real-world elements of having humans around the process of delivering packages. These options dynamically introduce new entities into the simulation, each playing a role in the delivery process. Lastly, there is a 'Stop Simulation' button that, when pressed, stops the ongoing simulation and exits the program. This setup not only showcases the operational dynamics of a drone delivery service but also allows interaction and the administration of the stop command embedded into the simulation which is an exit status option for the user to quit the simulation after performing the required actions with the provided map and interactive entities.



We added a feature that allows users to manually create restore points, load restore points, and reset to the original state of the entire simulation using manual buttons in the simulation. Specifically, while creating restore points, it takes a snapshot of the simulation for all entities in existence at that time and stores this snapshot. While loading the restore point, the last created restore point’s snapshot is used to update all the entities with their states at that point in time. During this process, any entities that did not exist at the time of the snapshot are removed to accurately restore the simulation to that state. Lastly, the reset functionality reverts the simulation to its initial state upon loading, effectively restoring the simulation to its beginning configuration. This feature contributes towards error management as the state of the simulation can be reset or loaded from a restore point if an undesired delivery is scheduled or the state of the simulation is reached. Additionally, the feature allows one to gain another layer of understanding of the functionality of the simulation specifically, the relation between the entities and the extent to which each entity is restored (or even removed) by tangible interaction to control the simulation effectively.

We used the Memento design pattern to implement this feature as it directly aligned with the state preservation and restoration requirement the feature is addressing. Using a Memento design pattern, we represented a snapshot of the simulation through a memento and created a caretaker to handle all operations with these snapshots/Mementos (creating and loading). This framework provides more enhanced functionality with the incorporation of memento and caretaker and security with the help of encapsulation of the entities captured in each snapshot.


The dashboard of the simulation consists of 3 buttons:

1. “Create Restore Point”

By pressing this button, it captures a snapshot of the current simulation, specifically the existence and state of all the entities at that point in time

2. “Load Restore Point”

By pressing this button, it loads the last created restore point at that time, specifically updating the existence of all the entities and their states based on their previous captured state

3. “Reset Simulation”

By pressing the button, it resets the simulation to its initial state upon loading, specifically updating the entities to their beginning configuration


We have implemented a feature to collect the data from the simulation based on the entity interaction with other entities to analyze the lower scale model on a large business scale perspective. It mainly collects various metric data points for entities such as drones, robots, and packages. It is interesting because the collection of metrics such as average speed, number of deliveries, total distance traveled, total delivery time, and pickup and dropoff coordinates for drones will give a good estimate and perspective on how to improve the idea of drone delivery system when being implemented on a large scale business. This is because simulations are cost-effective ways of identifying and understanding a specific part of any software mainly addressing the issue to maximize the efficiency with minimum resources and still maintain a good monetary income for the product to keep running in the local and global markets. These data points will let the creator or the company help in analyzing the inefficiencies that can be improved to develop a more robust and effective system as real-world expenses on running such a complex system systems will require many resources. In the mindset, to utilize all resources efficiently and to serve the purpose of the simulation model, these data points will help in analyzing the situations more effectively. In addition to the existing simulation, the extension takes in an extra class which single-handedly is responsible for handling the collection of data which is extended to various entities and sent to a specific output location to store data. The design pattern chosen for the extension implementation is the Singleton pattern and the reason for this design pattern is that we wanted to ensure that there is only one instance of the ⁠class responsible for data collection throughout the simulation. This is important since multiple instances would lead to conflicts in the data collection such as data duplication or inconsistencies. Most importantly, the Singleton pattern provides a global point of access to the ⁠ DataCollector ⁠ instance which is beneficial for various parts of the simulation and eliminates the need to pass the ⁠ DataCollector ⁠ instance around reducing coupling. There is no specific procedure to simulate this extension as it is not user interactable rather the user can follow the steps for running the simulation as described in the earlier section above and try out various patterns with the drone and delivering packages, and lastly, at the end of stop administration command there would be a couple of CSV files available in the project directory which can be opened to view the collected data.



![WhatsApp Image 2024-05-05 at 22 46 57](https://media.github.umn.edu/user/27146/files/33647c37-75e1-4c28-beea-8d45d220e123)



Data Analysis:
Find different data sets and graphs by following the links to these two Excel sheets. 
[Excel 1](https://docs.google.com/spreadsheets/d/1P5igbTkiQJQlGSdLBzKcYXwU2VSWvy6TnFJwBvVBAwk/edit#gid=2030865217)
[Excel 2](https://docs.google.com/spreadsheets/d/1T1NkYQs8Z000cRWlfgMSpMzMzqPoMcqKjnacRHsKHY8/edit#gid=0)

Running simulations and collecting data points from drone operations provides us:

Optimize Routes: Identifies the most efficient paths to minimize travel time and fuel consumption, leading to cost savings.

Balance Workload: Evenly distribute deliveries among drones to maximize throughput and minimize wear and tear.

Scalability Analysis: We can understand how the system performs under different loads to guide future expansion and resource allocation.

Service Improvement: Analyzes delivery times and operational efficiency to enhance customer satisfaction and reliability.

Operational Efficiency:

Average Speed vs. Time Taken: We can see that higher speeds don't always correlate with faster delivery times due to route complexities. 
[Excel 1](https://docs.google.com/spreadsheets/d/1P5igbTkiQJQlGSdLBzKcYXwU2VSWvy6TnFJwBvVBAwk/edit#gid=2030865217)


Solution: Businesses should focus on optimizing routing algorithms, such as implementing dynamic and adaptive pathfinding based on real-time data, rather than solely increasing drone speed.


Number of deliveries per drone vs the total time taken:

As we can see in the graph, balancing the delivery load across drones can significantly reduce overall delivery times, enhancing operational efficiency and reducing drone wear and tear. 
[Excel 1](https://docs.google.com/spreadsheets/d/1P5igbTkiQJQlGSdLBzKcYXwU2VSWvy6TnFJwBvVBAwk/edit#gid=2030865217)

Average speed vs total distance:
Here, the graph shows that while drones maintain consistent speeds, the variation in total distance traveled suggests a need for more efficient route planning to reduce operational costs and improve fuel efficiency.
[Excel 1](https://docs.google.com/spreadsheets/d/1P5igbTkiQJQlGSdLBzKcYXwU2VSWvy6TnFJwBvVBAwk/edit#gid=2030865217)
[Excel 2](https://docs.google.com/spreadsheets/d/1T1NkYQs8Z000cRWlfgMSpMzMzqPoMcqKjnacRHsKHY8/edit#gid=0)



