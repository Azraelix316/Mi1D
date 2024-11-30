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

### Analysis
![Hump-like graph showing infections vs. time](images/disease_outbreaks.png) The data shows a typical epidemic - people get exposed, slowly building up the exposed population, which is then reflected into the infected population. The epidemic peaks, and then goes back down as people recover or die. The model is able to generate a variety of graphs like this, predicting a random outcome that could occur, given infection rates and recovery/mortality rates. This graph is commonly accepted as a "normal" epidemic, and is a great, simple model to explain the progress and stages of an epidemic.

### Strengths
The "best" model is the SEIRD model, so the strengths are mainly on that one. SEIRD is able to model a lot of epidemics, with deaths, exposure, latency times which really increase it's accuracy - but as always, the model depends on a lot on how accurate the data you can feed into it is. It uses a deque to help model exposures and infections, and it still has a lot more features that can be added to improve. My implemenatation is also probabilistic, so you get the variance one would expect from random interactions and infection rates. The most important part is that this model sufficiently demonstrates the "curve" or trajectory that a typical epidemic would take, which is useful to see a variety of effects: for example, an extremely large latency time combined with a high transmission rate like COVID-19.

### Improvements
Some improvements that can be made are more realistic methods to simulate the variance, for example an actual simulation. Additionally, analytical methods can be used for all of the ODE versions. The most limiting factor is the inability to test this, there is no way to double check to see if the model will accurately predict how an epidemic progresses - it only produces a graph based on the input variables. Additionally, more functionality such as vaccinations or changing exposure times can really help model real life situations.

## Model 2: Deforestation pt. 1 
### Summary
Date: 11/27/2024 (Research & Code in 1 day)
<br>
<br>
To be completely honest, this model is gutter trash. Deforestation was a really difficult topic, especially since it's so nuanced that it's extremely hard to model well in one day - but that's exactly why I'm doing this. This model in particular was research intensive, as the model design was way more difficult than the actual implementation. At first, I was going to go with an economic-centric design, but then it was a lot easier to just make a trend model as the goal was to predict the results of deforestation.
The model is extremely simple, just a linear trend, with a lot of unit conversions to calculate the CO2 emissions, temperature growth, and the tree loss. It outputs a predicted temperature growth due to deforestation for 60 years.
This model will probably be redone when I have a chance to.

### Analysis
![Exponential growth of temperature vs. years](images/deforestation_effects.png)
The data shows that as deforestation trends continue to increase, eventually deforestation will account for a 0.8 celsius increase in global temperatures. An interesting thing to note is that the curve is increasing, which means that the temperature growth will continue to accelerate as demand for land and trees increase - causing accelerated tree loss and deforestation.


### Strengths
The model is extremely simple, able to run quickly and have multiple extra features. The simplicity also helps with accuracy, as it's very hard to mess up the simple unit conversions. The model is also able to extrapolate from the predictions what the actual "hard" effects are - temperature growth and CO2 increases. It is very good at showing the effects.
Other than that, this model has barely any other strengths.

### Improvements
The model could use some more nuanced predictions, such as using forecasting methods such as the Holt-Winters method or other ways to predict the tree loss. Additionally, more features could be used. The base is also flawed, as there are better ways to model deforestation, such as an agent-based way or more simulation-based way to model deforestation. The model is only capable of giving a scenario assuming that current trends continue linearly, which may not occur. I believe that the model was too simple for such a complex problem, and it's one of the things I want to fix.




