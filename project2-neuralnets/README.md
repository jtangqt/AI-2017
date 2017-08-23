#Project 2 - Training and Testing of Neural Networks

This is the second project for AI Independent Study with Professor Sable. 

## How to Run:
Run main.m through either MATLAB or Octave

```

## Dataset Explanation:
I found a dataset online for SPY. SPY is an ETF that I'm particularly fond of and following. 
In each dataset, the input nodes are opening value, highest value, lowest value and volume during that specific day. The output nodes represented the closing value of that specific day. 

```

## To Normalize the Data:
For opening value, highest value and lowest value, I took the minimum of all of these numbers and subtracted each number by this value. I then divided all numbers by 100: (value - min(values))/100
For the volume, I took the minimum and maximum of the volumes. I computed each value this way: (value - min)/(max - min) to normalize the volume 

## To Create Initial Neural Network:
I randomized numbers from 0 to 1 to create the initial weights for the neural network 

```

## Ultimate Epochs, Alpha and Number of Hidden Nodes
Epochs: 400 (500 for more accuracy, precision, recall, and F1)
Alpha: 0.1
Hidden Nodes: 15

