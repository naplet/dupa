#include <string>
#include <algorithm>
#include<iostream>
#include "Polybius.h"


std::string PolybiusCrypt(std::string message)
{
    int k = message.length();
    std::string message2;
    std::string var = "j";
    std::string alfabet = "abcdefghiklmnopqrstuvwxyz ";
    std::string tab[26] = {"11","12","13","14","15","21","22","23","24","25","31","32","33","34","35","41","42","43","44","45","51","52","53","54","55",""};
    std::transform(message.begin(), message.end(), message.begin(),::tolower);
    for(int i=0;i <k;i++)
    {
        for(int j=0;j<26;j++)
        {
            if(message[i]==alfabet[j]) {
                message2.append(tab[j]);
                break;
            }
            if(message[i]==var[0])
            {
               message2.append("24");
                break;
            }
        }
    }
    return message2;
}

std::string PolybiusDecrypt(std::string crypted)
{
    int k = crypted.length();
    std::string tmp[1];
    std::string message2;
    std::string alfabet[25] = {"a","b","c","d","e","f","g","h","i","k","l","m","n","o","p","q","r","s","t","y","v","w","x","y","z"};
    std::string tab[25] = {"11","12","13","14","15","21","22","23","24","25","31","32","33","34","35","41","42","43","44","45","51","52","53","54","55"};
    for(int i=0;i <k;)
    {
        for(int j=0;j<25;j++)
        {
            tmp[1]=crypted[i]+crypted[i+1];
            if(tmp[1]==tab[j])
            {
                message2.append(alfabet[j]);
                break;
            }
            i=i+2;
        }
    }
    return message2;
}
