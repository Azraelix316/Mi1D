# Summary
The problem is to find a way to model the spread of outbreaks and epidemics. Especially since the COVID-19 pandemic, it is a pressing issue to determine how to calculate the spread and quantify the effects of measures such as social distancing.
Common models used are compartmental models, which is implemented with multiple different variations here. Compartmental modals split the population into different groups, such as infected or susceptible, and use these groups to model how a disease progresses. While the implementation is simple, it's able to demonstrate the basic shape of epidemics and has multiple variables that can be modified. Using these models, I created a lot of extensions to have more and more features, so there's even more data that can be analyzed to see how a disease progresses.
The implementations are as follows, with each building off the last:
1. An ODE implementation
2. A stochastic version
3. SIRD
4. SEIR(D)
<!---->
All of them give similar graphs and have their own strengths and advantages, and the hope is to get familiar with these models. <br>
Date: 11/24/2024 (Research & Code)
