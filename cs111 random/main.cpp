#include <iostream>
#include <cmath>
    #include <algorithm>
#include <vector>

using namespace std;

bool primality(int n)
{
    //based on def of primality from slides
    if (n <= 1) {return false;}
    if (n <= 3) {return true;} // covers two and 3
    if (n%2 == 0 || n%3 == 0){ return false;}
    for (int i = 5; pow(i, 2) <= n; i = i + 6)
    {
        if (n%i == 0 || (n+2)%i == 0)
        {
            return false;
        }
    }
    return true;
}

bool checkInvalidInput(int e, int n, int p, int q)
{
    int phi = (p-1) * (q-1);
    if (e >= n || __gcd(e, phi) != 1 || p == q || !primality(p) || !primality(q))
    {
        cout << "Public key is not valid!";
        return true;
    }
    return false;
}

vector<int> genPrimeFactors(int n)
{
    
    vector<int> primeFactors;
    while (n % 2 == 0) {
        primeFactors.push_back(n);
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            primeFactors.push_back(i);
            n = n / i;
        }
    }

    if (n > 2) {
        primeFactors.push_back(n);
    }
    return primeFactors;
}


int inverseMod(int e, int phi) // for d = e^-1 (mod phi)
{
    e = e % phi;
    int i = 0;
    while (i < phi - 1)
    {
        if ((e * i) % phi == 1)
        {
            return i;
        }
        i++;
    }
    return -1;
}

int modExp(int C, int d, int n) //for c^d (mod n)
{
    // https://en.wikipedia.org/wiki/Modular_exponentiation
    int c = 1;
    int i = 0;
    while (i < d)
    {
        i++;
        c = fmod((C*c), n);
    }
    return c;
}

int main()
{
    
    int e, n;
    cin >> e >> n;
    int m;
    cin >> m;
    
    vector<int> primes = genPrimeFactors(n);
    int p = primes.at(0);
    int q = primes.at(1);
    int phi = (p-1) * (q-1);

    if (checkInvalidInput(e, n, p, q))
    {
        exit(1);
    }

    int d = inverseMod(e, phi);
    cout << p << " " << q << " " << phi << " " << d << endl;
 
    vector<int> encryptedMessage;
    for (int i = 0; i < m; i++)
    {
        int cow;
        cin >> cow;
        encryptedMessage.push_back(cow);
    }


    vector<int> decrypted;
    vector<char> characters;
    for (int i = 0; i < encryptedMessage.size(); i++)
    {
        int M = modExp(encryptedMessage.at(i), d, n);
        decrypted.push_back(M);
        if (M < 33)
        {
            characters.push_back('A' + (M - 7));
        }
        else if (M == 33)
        {
            characters.push_back(' ');
        }
        else if (M == 34)
        {
            characters.push_back('"');
        }
        else if (M == 35)
        {
            characters.push_back('.');
        }
        else if (M == 36)
        {
            characters.push_back(',');
        }
        else if (M == 37)
        {
            characters.push_back('\'');
        }
        
    }

    for (int i = 0; i < decrypted.size(); i++)
    {
        cout << decrypted.at(i) << " ";
    }
    cout << endl;
    for (int i = 0; i < characters.size(); i++)
    {
        cout << characters.at(i);
    }

    return 0;
}
