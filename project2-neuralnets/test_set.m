function [table] = test_set(X, y, trained_nn) 

m = size(X, 1); 

output_nodes = trained_nn(1,3); 

table = zeros(output_nodes, 4); 
y_pred = zeros(1,output_nodes); 

hidden_nodes = trained_nn(1,2);
weights_pre_inner = trained_nn(2:hidden_nodes+1, :); 
weights_pre_outer = trained_nn(hidden_nodes+2:end, :); 
weights_inner = weights_pre_inner(:, 1:size(X,2)+1);
weights_outer = weights_pre_outer(:, 1:hidden_nodes+1); 

for i = 1:m
   a_1 = [-1; X(i, :)'];  
   in_i = weights_inner*a_1; 
   a_2 = [-1; sigmoid(in_i)]; 
   in_j = weights_outer*a_2; 
   h = sigmoid(in_j); 
   
   for j = 1:size(y, 2) 
       if(h(j) < 0.5)
           y_pred(j) = 0;
       elseif (h(j) >= 0.5)
           y_pred(j) = 1; 
       end 

       if (y(i, j) == 1 && y_pred(j) == 1)
           table(j, 1) = table(j, 1) + 1;
       elseif(y(i, j) == 1 && y_pred(j) == 0)
           table(j, 3) = table(j, 3) + 1; 
       elseif(y(i, j) == 0 && y_pred(j) == 1)
           table(j, 2) = table(j, 2) + 1; 
       elseif(y(i, j) == 0 && y_pred(j) == 0)
           table(j, 4) = table(j, 4) + 1; 
       end
   end
   
end

end