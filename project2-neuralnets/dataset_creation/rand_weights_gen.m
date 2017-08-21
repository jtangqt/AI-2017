rng(0, 'twister');

hidden_nodes = 15;
input_nodes = 7;
output_nodes = 4; 

total = hidden_nodes*(input_nodes+1)+output_nodes*(hidden_nodes+1); 

r = rand(total, 1);

fid = fopen('new_nn.txt', 'wt'); % Open for writing
    for i=1:hidden_nodes
        for j = 1:input_nodes+1
            fprintf(fid, '%.3f ', r((i-1)*(input_nodes+1)+j));
        end 
        fprintf(fid, '\n');
    end
    for i = 1:output_nodes
        for j = 1:hidden_nodes+1
            fprintf(fid, '%.3f ', r((i-1)*(input_nodes+1)+j));
        end 
        fprintf(fid, '\n');
    end
    fclose(fid);