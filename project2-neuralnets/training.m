init = importdata('init_neural_net.mat'); 
trained = importdata('training_set.mat'); 

input_nodes = init(1,1); % # of input nodes

X = trained(:, 1:input_nodes); 
y = trained(:, input_nodes+1); 

neural_net = BackProp(X, y, init, 100, 0.1); 


%B = reshape(data(2:end -1 , :), hidden_nodes, input_nodes); 