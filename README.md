# Motivation
All of these models were created in one day or less, in order to prepare for competitions such as the MCM and the HiMCM. 
These competitions require not only good models, but also a lot of knowledge on a variety of models. As such, all of the ideas (created with ChatGPT) can be solved with a variety of models.
All of the code is in c++ and research AND code had to be conducted in one day, in order to meet the speed requirements that these competitions have. Additionally, this training forces me to learn a variety of models for different use cases.
As a personal rule, I don't use any libraries except for the std libraries, in order to force myself to learn more key concepts and really learn the implementations deeply. 

## Model 1: Pandemic Modeling (SEIRD) 
### Summary
Date: 11/24/2024 (Research & Code in 1 day)
<br>
<br>
The problem is to find a way to model the spread of outbreaks and epidemics. Especially since the COVID-19 pandemic, it is a pressing issue to determine how to calculate the spread and quantify the effects of measures such as social distancing.
Common models used are compartmental models, which is implemented with multiple different variations here. Compartmental modals split the population into different groups, such as infected or susceptible, and use these groups to model how a disease progresses. While the implementation is simple, it's able to demonstrate the basic shape of epidemics and has multiple variables that can be modified. Using these models, I created a lot of extensions to have more and more features, so there's even more data that can be analyzed to see how a disease progresses.
The implementations are as follows, with each building off the last:
1. An ODE implementation of SIR
2. A stochastic version of model 1
3. SIRD
4. SEIR(D)
<!---->
All of them give similar graphs and have their own strengths and advantages, and the hope is to get familiar with these models. <br>

### Strengths
The "best" model is the SEIRD model, so the strengths are mainly on that one. SEIRD is able to model a lot of epidemics, with deaths, exposure, latency times which really increase it's accuracy - but as always, the model depends on a lot on how accurate the data you can feed into it is. It uses a deque to help model exposures and infections, and it still has a lot more features that can be added to improve. My implemenatation is also probabilistic, so you get the variance one would expect from random interactions and infection rates. The most important part is that this model sufficiently demonstrates the "curve" or trajectory that a typical epidemic would take, which is useful to see a variety of effects: for example, an extremely large latency time combined with a high transmission rate like COVID-19.

### Improvements
Some improvements that can be made are more realistic methods to simulate the variance, for example an actual simulation. Additionally, analytical methods can be used for all of the ODE versions. The most limiting factor is the inability to test this, there is no way to double check to see if the model will accurately predict how an epidemic progresses - it only produces a graph based on the input variables. Additionally, more functionality such as vaccinations or changing exposure times can really help model real life situations.



