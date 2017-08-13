function neural_net = BackProp(X, y, weights_1, weights_2, epoch, alpha)

n = size(X, 1); 
m = 0; 

while (m < epoch)
   for t = 1:n
       a_1 = X(t, :); 
      
       %For hidden layer
       a_1 = [-1; a_1']; 
       in_1 = weights_1*a_1; 
       a_2 = sigmoid(in_1); 
      
       %For output layer
       a_2 = [1; a_2]; 
       in_2 = weights_2*a_2; 
       a_3 = sigmoid(in_2); 
       
       delta_2 = sigmoid_prime(in_2).*(y(t)-a_3); 
       
       delta_1 = [1; sigmoid_prime(in_1)]*sum(sum(weights_1))*delta_2; 
       
       weights_1(t, :) = weights_1(t, :) + alpha*a_1'*delta_1; 
       weights_2(t, :) = weights_2(t, :) + alpha*a_1*delta_2;
       
   end   
    m = m+1; 
    neural_net = 0; 
end


end