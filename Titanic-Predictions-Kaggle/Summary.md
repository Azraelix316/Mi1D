# Summary
Date: 12/3/2024 - 12/4/2024 (Code in 2 days)
<br>
<br>
This model was an application of a generalized linear regression model that I created over 12/1-12/2, which utilizes coordinate descent. The data used was from the Titanic competition on kaggle.com, so there was almost no research. The model was relatively easy to create, but since the values in the end had to be 0 or 1, I used a basic logistic regression by adding a cutoff value and rounding. After I found a reasonable solution, I continued on for another day to try to keep improving the solution even further with new functions.

## Analysis
Overall, the performance of this model is fine, with an R-squared of ~0.5 and an accuracy of around 80%, which puts this model (as of the date of writing) in the top quartile of models. The coordinate descent worked very fast and identified a "good" solution very quickly.I also implemented in simple ridge regularization, in order to minimize variance as I found that the model would overfit. Even after training to a higher r-squared, the model failed to produce high accuracy, so ridge regression improved variance, but lowered bias.

## Strengths
Since the model is a logistic regression, cutoff values can also be optimized, which helps to improve accuracy as the model does not have to be exact. Additionally, the linear regression sufficiently models basic relationships very well. This allows it to have a high accuracy rate, nearly 80% with a short training period and a simple model - which is important for short competitions. This shows how powerful linear regression is, and gives me a good tool for a wide variety of future competitions.

## Improvements
Most of the relationships aren't linear, so the linear regression fails to model these complex relatioships. Additionally, the model could be improved to further minimize bias, with more features or going into polynomial regressions. The generalized linear regression that this model is built on could be optimized to become true generalized regression, able to also have bayesian or different stochastic models. 