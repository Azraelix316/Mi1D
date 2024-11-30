# Summary
Date: 11/27/2024 (Research & Code in 1 day)
<br>
<br>
To be completely honest, this model is gutter trash. Deforestation was a really difficult topic, especially since it's so nuanced that it's extremely hard to model well in one day - but that's exactly why I'm doing this. This model in particular was research intensive, as the model design was way more difficult than the actual implementation. At first, I was going to go with an economic-centric design, but then it was a lot easier to just make a trend model as the goal was to predict the results of deforestation.
The model is extremely simple, just a linear trend, with a lot of unit conversions to calculate the CO2 emissions, temperature growth, and the tree loss. It outputs a predicted temperature growth due to deforestation for 60 years.
This model will probably be redone when I have a chance to.

## Analysis
![Exponential growth of temperature vs. years](image.png)
The data shows that as deforestation trends continue to increase, eventually deforestation will account for a 0.8 celsius increase in global temperatures. An interesting thing to note is that the curve is increasing, which means that the temperature growth will continue to accelerate as demand for land and trees increase - causing accelerated tree loss and deforestation.


## Strengths
The model is extremely simple, able to run quickly and have multiple extra features. The simplicity also helps with accuracy, as it's very hard to mess up the simple unit conversions. The model is also able to extrapolate from the predictions what the actual "hard" effects are - temperature growth and CO2 increases. It is very good at showing the effects.
Other than that, this model has barely any other strengths.

## Improvements
The model could use some more nuanced predictions, such as using forecasting methods such as the Holt-Winters method or other ways to predict the tree loss. Additionally, more features could be used. The base is also flawed, as there are better ways to model deforestation, such as an agent-based way or more simulation-based way to model deforestation. The model is only capable of giving a scenario assuming that current trends continue linearly, which may not occur. I believe that the model was too simple for such a complex problem, and it's one of the things I want to fix.



