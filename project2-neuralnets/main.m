prompt = 'Would you like to train or test? '; 
train_test = input(prompt, 's'); 
i = 0; 

while (i == 0)
    if (strcmp(train_test, 'train'))
        training;
        prompt = 'Would you like to now test this trained neural network? (Y/N) '; 
        answer = input(prompt, 's'); 
        if(strcmp(answer, 'Y'))
            %something
            train_test = 'test';
        elseif(strcmp(answer, 'N'))
            %something else
            i = 1; 
        end
    elseif (strcmp(train_test, 'test'))
        test; 
        i = 1; 
    end
end