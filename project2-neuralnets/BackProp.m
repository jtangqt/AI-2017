function neural_net = BackProp(X, y, init, epoch, alpha)

n = size(X, 1); 
m = 0; 
neural_net = init(2:end, :); 

hidden_nodes = init(1,2); % # of hidden nodes
output_nodes = init(1,3); % # of output nodes
weights_inner = init(2:hidden_nodes+1, :); % weights of edges pointing from input to hidden
weights_outer = init(hidden_nodes+2:end, :); % weights of edges pointing from hidden to output 
weights_outer(isnan(weights_outer)) = []; 

while (m < epoch)
   for t = 1:n
       a_1 = X(t, :); 
      
       %For hidden layer
       a_1 = [-1; a_1']; 
       in_i = weights_inner*a_1; 
       a_2 = sigmoid(in_i); 
      
       %For output layer
       a_2 = [1; a_2]; 
       in_j = weights_outer*a_2; 
       a_3 = sigmoid(in_j); 
       
       delta_j = sigmoid_prime(in_j)*(y(t)-a_3); 
       
       delta_i = [1; sigmoid_prime(in_i)]*sum(weights_outer*delta_j); 
       
       weights_inner(t, :) = weights_inner(t, :) + alpha*a_1'*delta_i; 
       weights_outer(t, :) = weights_outer(t, :) + alpha*a_2'*delta_j;
       a
   end   
    m = m+1; 
    neural_net(1:hidden_nodes, :) = weights_inner; 
    neural_net(hidden_nodes+1:end,:) = weights_outer; 
end


end