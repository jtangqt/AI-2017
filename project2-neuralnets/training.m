prompt = 'What is the name of the text file with the initial neural network? ';
init_neural_net = input(prompt,'s');

prompt = 'What is the name of the text file with the training set? ';
training_set = input(prompt,'s');

prompt = 'What is the name of the text file for the output? ';
output_file = input(prompt,'s');

init = importfile(init_neural_net); 
trained = importfile(training_set); 

input_nodes = init(1,1); % # of input nodes

X = trained(:, 1:input_nodes); 
y = trained(:, input_nodes+1); 

neural_net = BackProp(X, y, init, 1, 0.1); 

fid = fopen(output_file, 'wt'); % Open for writing
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