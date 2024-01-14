
# Smart Traffic Management System

**Problem**

- The time provided for green light at a traffic junction is a constant, which introduces inefficiencies.
- No formal means to provide a smooth passage for ambulance at a traffic junction.

**Overview**

Smart Traffic Management System is a product whose main aim is to achieve
the following:-
- Analyze the traffic density, and dynamically determine the duration of green light on each side if the traffic junction.
- Provide a traffic-free road clearance to ambulances in the case of emergencies so that they can reach their destination as fast as possible. This concept is known as “Green Corridor".

This product is being made by 7 students of IIIT-B of the IMT2022 batch for
the electronics lab project for the academic year 2023-24.

**Inspiration**

Every day in India, an average of 24,012 patients die due to delay in getting
adequate medical help/attention as ambulances are delayed due to traffic.

Also, in a recent survey, there were 2 Indian cities (Bengaluru and Pune)
among the top 10 cities in the world in terms of traffic congestion and delay.
A study
estimated that Bangalore loses over $6 billion in productivity each year.

Our team decided to come up with a system which could solve these
issues, provide a path with relatively less traffic to ambulances which are
carrying a patient and try to reduce the density of traffic in an area in
general.

**Specifications**
- Green Corridor
Our system involves the use of radio-frequency identification(RFID) tags and
readers to achieve the goal of creating a green corridor for ambulances. The
ambulances will each have a radio frequency identification tag, which will
emit a radio signal when it is in relative proximity of a RFID reader(traffic
signal), which will be picked up by the RFID reader present at the traffic
signal, and turn to green in order to allow the ambulance to go through
quickly.

- Traffic Density Management
We will install servo motors on street lights and attach ultrasonic sensor to it. The ultrasonic sensors face down towards the road and are turned to 3 discrete angles. They are used to check if any vehicle is present at the angle that is being viewed. Using this, the distance upto where the traffic goes can be determined.

This solution solves the problems discussed above.


## Demo

[Circuit Diagrams](https://iiitbac-my.sharepoint.com/:o:/g/personal/ys_snigdha_iiitb_ac_in/EhYcur4nRAhCggWFZ0XxJOkBAf0FH3cQ_LHfi0f7rmfYKQ?rtime=bebPHLcU3Eg)

[Demonstration video](https://drive.google.com/file/d/1SUQRCOl5IYwi3PxgXnE-TGo2aEvK0LLi/view?usp=sharing)


## Future enhacements to the solution

- The number of discrete angles that the ultrasonic sensor views can be increased to improve accuracy of traffic density determination.
- Using the data accumulated, to predict traffic and send notification to traffic police office who can take the necessary action. 
- Creating an interconnected traffic management system by implementing IoT to establish connection between multiple traffic junctions. This can be used to improve co-ordination between multiple junctions. For example: if it takes 1.5 min on average to get from juntion A to juntion B. The traffic light should turn green at junction B 1.5 min after junction A turned green to reduce overall wait time.


## Contributors

- [Pradyumna G](https://github.com/PradyumnaG)
- [Harshavardhan R](https://github.com/Harshblah)
- [Aryan Mishra](https://github.com/the-aryanmishra)
- [Sreyas Janamanchi](https://www.linkedin.com/in/sreyas-janamanchi-932569261/)
- [Nupur Patil](https://www.linkedin.com/in/nupur-patil-87b9a5250/)
- [Sasi Snigdha](https://github.com/Snigdha2005)
- [Ishan Jha](https://github.com/Ishaniiitb)

