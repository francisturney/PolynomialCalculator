#include "calculate.h"



namespace Calculate
{
void normalize(string &input)
{
    for(int i = 0; i < input.size(); i++)
    {
        while(input[i] == ' ')
            input.erase(i,1);
        input[i] = tolower(input[i]);
    }
}

QString process(string &input, expression list[])
{
    QString out("");
    static string commandSet[] ={"let","print", "eval", "plot", "save as", "open"};
    normalize(input);
    int pos;
    for(int i = 0; i < 3; i++)
        if((pos = input.find(commandSet[i])) < string::npos || input.find("saveas") || input.find("open"))
                break;
    if(pos < string::npos || input.find("saveas") || input.find("open"))
        out = doCommand(input,list);

    return out;

}


QString doCommand(string &input, expression *list)
{
    int pos;
    QString outFile;

    if(input.find("saveas") < string::npos)
    {
        string callFile;
        input = input.substr(6);
        ofstream outStream(input.c_str());
        if(outStream.fail())
        {
            throw COULDNT_SAVE;
        }
        //write to file
        char F('a');
        int i = 0;
        F = 'a' + i;
        outStream << F <<" = " << list[0 + i] << endl;
        while(outStream && i < 25)
        {
            i++;
            F = 'a' + i;
            outStream << F <<" = " << list[0 + i] << endl;
        }
        outStream.close();

        outFile.append("File saved as ");
        outFile.append(outFile.fromStdString(input));
        return outFile;

    }
    else
        if(input.find("open") < string::npos)
        {

            input= input.substr(4);
            ifstream inStream(input.c_str());
            if(inStream.fail())
            {
                throw BAD_OPEN;
            }
            //save to program memory
            int i = 0;
            char temp;
            temp = inStream.peek();
            inStream >> list[temp - 'a'];
            while(inStream && i < 25)
            {
                if(list[inStream.peek()-'a'].used())
                    list[inStream.peek()-'a'].clear();
                inStream >> list[inStream.peek() - 'a'];
                i ++;
            }
//            cout << "\n" << callFile << endl << endl;
//            for ( i = 0; i < 25 ; i ++)
//            {
//                if(list[i].used())
//                    cout << char('a' + i) << " = " << list[i] << endl;
//            }
//            cout << endl;
            inStream.close();
            //cin.ignore();

        }
    else
    if(input.find("let") < string::npos)
    {

        input=input.substr(3);
        char result = input[0];
        string tempIn(input);
        stringstream ss;
        tempIn=tempIn.substr(2);
        int pos;
        if ((pos = tempIn.find_first_of("abcdefghijklmnopqrstuvwyz")< tempIn.size()))
        {
            assignment(tempIn, list, result);
            outFile.append(result);
            outFile.append(" = ");
            outFile.append(list[result-'a'].qS());
            return outFile;

        }
        ss<<input;
        //cout << endl << "input = " << input << " result = " << result;
        if(list[result-'a'].used())
            list[result-'a'].clear();
        ss>>list[result-'a'];
        outFile.append(result);
        outFile.append(" = ");
        outFile.append(list[result-'a'].qS());
        //qDebug()<<"out ecpression = "<< list[result-'a'].qS();
        return outFile;

    }
    else
        if(input.find("eval") < string::npos)
        {
            char who = input[4];
            pos = 0;
            while((pos = input.find_first_of("abcdedfhijklmnopqrstuvwyz()")) < string::npos)
                input.erase(pos,1);

            string TempC;
            stringstream ss, dd;
            ss<<input;
            fraction where,ans;
            ss>>where;
            ans = list[who-'a'].evaluate(where);
            qDebug()<< "after eval ";
            cout<<who<<"("<<where<<") = "<<ans;
            dd<<who<<"("<<where<<") = "<<ans;
            getline(dd,TempC);
            outFile=outFile.fromStdString(TempC);
            return outFile;
        }
        else
            if(input.find("print") < string::npos)
            {
                string exp = input.substr(5);
                QChar outChar(exp[0]);
                outFile.append(outChar);
                //qDebug()<<"outchar = "<< outChar;
                outFile.append(" = ");
                QString pExp;
                pExp = list[exp[0] -'a'].qS();

                outFile.append(pExp);
                //cout << "input = " << input;
                return outFile;

            }
            else
                if(input.find("plot")  < string::npos)
                {

                }
                else
                {
                    outFile.append("Invalid input. Please re-enter");
                    return outFile;
                }
}

void assignment(string &input,expression *list, char result)
{

    //cout << "\nin assignment\n";
    int pos;
    pos = input.find_first_of("+-*");
    if(pos < string::npos)
    {
        char x = input[pos-1], y = input[pos+1];
        cout << "x = " << x << " y = " << y <<endl;
        switch(input[pos])
        {
            case '+': list[result - 'a'] = (list[x-'a']+list[y-'a']);
                      break;

            case '-': list[result - 'a'] = list[x-'a']-list[y-'a'];
                      break;

            case '*': list[result - 'a'] = list[x-'a']*list[y-'a'];
                      break;
        }
    }
    else
        if((pos = input.find("\'")) < string::npos)
        {
            cout << "\nin derivative\n pos = " << pos << " input[pos]  = " << input[pos] << endl;
            int count = 1;
            char x = input[pos-1];
            while((pos = input.find("\'", pos + 1))< string::npos)
                count++;
            list[result-'a'] = list[x-'a'].derivative(count); //what do I do if there are more than one tick marks
        }
}
}
