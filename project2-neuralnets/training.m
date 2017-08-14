init = importfile('init_neural_net.txt'); 
trained = importfile('training_set.txt'); 

input_nodes = init(1,1); % # of input nodes

X = trained(:, 1:input_nodes); 
y = trained(:, input_nodes+1); 

neural_net = BackProp(X, y, init, 1, 0.1); 

fid = fopen('my_trained_nn.txt', 'wt'); % Open for writing
for i=1:size(neural_net,1)
    for j = 1:size(neural_net, 2)
        if(isnan(neural_net(i, j)))
        elseif (i == 1)
            fprintf(fid, '%d ', neural_net(i,j)); 
        else
            fprintf(fid, '%.3f ', neural_net(i,j));
        end 
    end 
    fprintf(fid, '\n');
end
fclose(fid);