function neural_net = BackProp(X, y, init, epoch, alpha)

n = size(X, 1); 
m = 0; 
neural_net = init(1:end, :); 

hidden_nodes = init(1,2); % # of hidden nodes
% output_nodes = init(1,3); # of output nodes
weights_inner = init(2:hidden_nodes+1, :); % weights of edges pointing from input to hidden
weights_outer = init(hidden_nodes+2:end, :); % weights of edges pointing from hidden to output 
weights_outer(isnan(weights_outer)) = []; 

while (m < epoch)
   for t = 1:n
       a_1 = X(t, :); 
       a_1 = [-1; a_1']; 
      
       %For hidden layer
       in_i = weights_inner*a_1; 
       a_2 = sigmoid(in_i); 
       a_2 = [-1; a_2]; 
      
       %For output layer
       in_j = weights_outer*a_2; 
       a_3 = sigmoid(in_j); 
       
       %Calculating deltas
       delta_j = sigmoid_prime(in_j)*(y(t)-a_3); 
       delta_i = sigmoid_prime(in_i)*sum(weights_outer*delta_j); 
       
       %Updating weights
       weights_inner = weights_inner + alpha*delta_i*a_1'; 
       weights_outer = weights_outer + alpha*delta_j*a_2';
       
   end   
    m = m+1; 
end
 neural_net(2:hidden_nodes+1, :) = weights_inner; 
 neural_net(hidden_nodes+2:end, 1:size(weights_outer,2)) = weights_outer; 

end