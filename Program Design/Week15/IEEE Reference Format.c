char* reference(char author[], char title[], char conference[], char location[], char date[], char ppdoi[]){
    static char result[300];
    
    strcat(result, author);
    strcat(result, ", \"");
    strcat(result, title);
    strcat(result, ",\" ");
    strcat(result, conference);
    strcat(result, ", ");
    strcat(result, location);
    strcat(result, ", ");
    strcat(result, date);
    strcat(result, ", ");
    strcat(result, ppdoi);
    strcat(result, ".");
    
    return result;
}

