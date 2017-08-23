mat = xlsread('SPY Index.xlsx');

new_vector = mat(:, 5); 
output_vector = zeros(size(new_vector, 1), 4); 

for i = 1:size(new_vector, 1)
    if(200 <= new_vector(i) && new_vector(i) < 207.5) 
        output_vector(i, :) = [1 0 0 0];
    elseif(207.5 <= new_vector(i) && new_vector(i) < 212.5) 
        output_vector(i, :) = [1 1 0 0];
    elseif(212.5 <= new_vector(i) && new_vector(i) < 217.5) 
        output_vector(i, :) = [0 1 0 0];
    elseif(217.5 <= new_vector(i) && new_vector(i) < 222.5) 
        output_vector(i, :) = [0 1 1 0];
    elseif(222.5 <= new_vector(i) && new_vector(i) < 227.5) 
        output_vector(i, :) = [0 0 1 0];
    elseif(227.5 <= new_vector(i) && new_vector(i) < 232.5) 
        output_vector(i, :) = [0 0 1 1];
    elseif(232.5 <= new_vector(i) && new_vector(i) < 240) 
        output_vector(i, :) = [0 0 0 1];
    end 
end

mat(:, 1:3) = (mat(:, 1:3)-min(min(mat(:, 1:3))))/100; 
mat(:, 4) = (mat(:, 4)-min(mat(:, 4)))/(max(mat(:,4))-min(mat(:,4))); 

new_mat = [mat(:, 1:4), output_vector];

fid = fopen('new_nn.txt', 'wt'); % Open for writing
    for i=1:size(new_mat,1)
        for j = 1:size(new_mat, 2)
            if (j > 4)
                fprintf(fid, '%d ', new_mat(i,j)); 
            else
                fprintf(fid, '%.3f ', new_mat(i,j));
            end 
        end 
        fprintf(fid, '\n');
    end
    fclose(fid);