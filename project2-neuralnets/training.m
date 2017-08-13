init = importdata('init_neural_net.mat'); 
trained = importdata('training_set.mat'); 

input_nodes = init(1,1); % # of input nodes
hidden_nodes = init(1,2); % # of hidden nodes
output_nodes = init(1,3); % # of output nodes
weights_inner = init(2:hidden_nodes+1, :); % weights of edges pointing from input to hidden
weights_outer = init(hidden_nodes+2, :); % weights of edges pointing from hidden to output 
weights_outer(isnan(weights_outer)) = []; 

X = trained(:, 1:input_nodes); 
y = trained(:, input_nodes+1); 


neural_net = BackProp(X, y, weights_inner, weights_outer, 100, 0.01); 


%B = reshape(data(2:end -1 , :), hidden_nodes, input_nodes); 