prompt = 'What is the name of the text file with the trained neural network? ';
trained_nn_file = input(prompt,'s'); %trained_neural_net.txt

prompt = 'What is the name of the text file with the test set? ';
test_file = input(prompt,'s'); %test_set.txt

prompt = 'What is the name of the text file for the output? ';
output_file = input(prompt,'s'); %results.txt

trained_nn = dlmread(trained_nn_file);
test = dlmread(test_file); 

input_nodes = trained_nn(1,1); % # of input nodes

X = test(2:end, 1:input_nodes); 
y = test(2:end, input_nodes+1:end); 

table = test_set(X, y, trained_nn); 

m = size(table, 1); 
A = table(:, 1);
B = table(:,2);
C = table(:,3);
D = table(:,4); 
new_table = [table, zeros(m, 4)]; 
mm_table = zeros(2, 4); 

for i = 1:m
    accuracy = (A(i)+D(i))/(A(i)+B(i)+C(i)+D(i));
    precision = A(i)/(A(i)+B(i));
    recall = A(i)/(A(i)+C(i));
    F1 = (2*precision*recall)/(precision+recall); 
    new_table(i, 5) = accuracy;
    new_table(i, 6) = precision;
    new_table(i, 7) = recall;
    new_table(i, 8) = F1; 
end

%this is for the micro-averaging
A_sum = sum(A);
B_sum = sum(B);
C_sum = sum(C);
D_sum = sum(D); 
    
mm_table(1,1) = (A_sum+D_sum)/(A_sum+B_sum+C_sum+D_sum);
mm_table(1,2) = A_sum/(A_sum+B_sum);
mm_table(1,3) = A_sum/(A_sum+C_sum);
mm_table(1,4) = (2*mm_table(1,2)*mm_table(1,3))/(mm_table(1,2)+mm_table(1,3)); 

mm_table(2,1) = sum(new_table(:,5)/m); 
mm_table(2,2) = sum(new_table(:,6)/m); 
mm_table(2,3) = sum(new_table(:,7)/m); 
mm_table(2,4) = (2*mm_table(2,2)*mm_table(2,3))/(mm_table(2,2)+mm_table(2,3)); 

fid = fopen(output_file, 'wt'); % Open for writing
for i=1:size(new_table,1)
    for j = 1:size(new_table, 2)
        if (j<=4)
            fprintf(fid, '%d ', new_table(i,j)); 
        else
            fprintf(fid, '%.3f ', new_table(i,j));
        end 
    end 
    fprintf(fid, '\n');
end

for i=1:size(mm_table,1)
    for j = 1:size(mm_table, 2)
        fprintf(fid, '%.3f ', mm_table(i,j));
    end 
    fprintf(fid, '\n');
end

fclose(fid);