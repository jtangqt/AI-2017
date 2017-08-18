prompt = 'What is the name of the text file with the initial neural network? ';
init_neural_net = input(prompt,'s'); %init_neural_net.txt

prompt = 'What is the name of the text file with the training set? ';
training_set = input(prompt,'s'); %training_set.txt

prompt = 'What is the name of the text file for the output? ';
output_file = input(prompt,'s'); %my_trained_nn.txt

prompt = 'How many number of epochs do you want? ';
epochs = input(prompt); 

prompt = 'What is the value of alpha? ';
alpha = input(prompt); 

init = dlmread(init_neural_net); 
trained = dlmread(training_set); 

input_nodes = init(1,1); % # of input nodes

X = trained(2:end, 1:input_nodes);
y = trained(2:end, input_nodes+1:end);

neural_net = BackProp(X, y, init, epochs, alpha); 

fid = fopen(output_file, 'wt'); % Open for writing
for i=1:size(neural_net,1)
    for j = 1:size(neural_net, 2)
        if(neural_net(i, j) == 0)
        elseif (i == 1)
            fprintf(fid, '%d ', neural_net(i,j)); 
        else
            fprintf(fid, '%.3f ', neural_net(i,j));
        end 
    end 
    fprintf(fid, '\n');
end
fclose(fid);