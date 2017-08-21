mat = dlmread('new_test_set.txt');

new_vector = mat(:, end); 
output_vector = zeros(size(new_vector, 1), 4); 

for i = 1:size(new_vector, 1)
    if(1.36 <= new_vector(i) && new_vector(i) < 1.38) 
        output_vector(i, :) = [1 0 0 0];
    elseif(1.38 <= new_vector(i) && new_vector(i) < 1.4) 
        output_vector(i, :) = [1 1 0 0];
    elseif(1.4 <= new_vector(i) && new_vector(i) < 1.42) 
        output_vector(i, :) = [1 1 1 0];
    elseif(1.42 <= new_vector(i) && new_vector(i) < 1.44) 
        output_vector(i, :) = [1 1 1 1];
    end 
end


new_mat = [mat, output_vector]


fid = fopen('new_test_set.txt', 'wt'); % Open for writing
    for i=1:size(new_mat,1)
        for j = 1:size(new_mat, 2)
            if (j > 8)
                fprintf(fid, '%d ', new_mat(i,j)); 
            else
                fprintf(fid, '%.3f ', new_mat(i,j));
            end 
        end 
        fprintf(fid, '\n');
    end
    fclose(fid);