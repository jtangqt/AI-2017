function g = sigmoid_prime(z)
    g = sigmoid(z).*(1-sigmoid(z));
end