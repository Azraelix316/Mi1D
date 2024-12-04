# Summary
Date: 12/3/2024 - 12/4/2024 (Code in 2 days)
<br>
<br>
This model was an application of a generalized linear regression model that I created over 12/1-12/2, which utilizes coordinate descent. The data used was from the Titanic competition on kaggle.com, so there was almost no research. The model was relatively easy to create, but since the values in the end had to be 0 or 1, I used a basic logistic regression by adding a cutoff value and rounding. After I found a reasonable solution, I continued on for another day to try to keep improving the solution even further with new functions.

## Analysis
Overall, the performance of this model is fine, with an R-squared of ~0.5 and an accuracy of around 80%, which puts this model (as of the date of writing) in the top quartile of models. The coordinate descent worked very fast and identified a "good" solution very quickly.I also implemented in simple ridge regularization, in order to minimize variance as I found that the model would overfit. Even after training to a higher r-squared, the model failed to produce high accuracy, so I tried to minimize variance.

## Strengths

## Improvements

