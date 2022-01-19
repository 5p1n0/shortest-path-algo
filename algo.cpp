#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

class graph
{
   int G[10][10];
   int S[10][10], Lj[10][10], Pj[10][10], n, i, j, k;
   public:
        void get_data();
        void mst();
        void print();
};

void graph::get_data()
{
  cout<<"\nEnter the total number of vertices: ";
  cin>>n;
  cout<<"\nEnter the adjacency matrix (If there is no edge betweent two vertex then enter 100): \n\n";
  
  for (i = 0; i < n; i++)
  {
       cout<<"___\n";

       for (j = 0; j < n; j++)
       {
             cin>>G[i][j];
       }
  }
}

void graph::mst()
{
  // Previous row min
  int old_min;

  // Min value 
  int min = 100;

  // Initial row
  int row = 0;

  // Rows search state 
  int selected[n];
  
  // Initial rows search state
  for (i = 0; i < n; i++)
  {
    selected[i] = false;
  }

  // S initialization
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      S[i][j] = 100;
    }
  }

  // Filled Pj first row 
  for (j = 1; j < n; j++) 
  {
    if (G[0][j] != 100) Pj[0][j] = 1;
    else Pj[0][j] = 100;
  }

  // Row holder
  int tmp_row;



  // Disordered search for all rows  
  for (int count = 0; count < n; count++)
  {
    // S update
    for (j = 0; j < n; j++) 
    {
      // Count next iterations 
      if (count != 0)
      {
        // Check previous row col value not 0
        if (S[count - 1][j] != 100)
        {
          // If true, copy it into the same col of the newer row
          S[count][j] = S[count - 1][j];
        } 
        // Check col == solution value
        else if (j == row) 
        {
          // Restoring proper value
          S[count][j] = row + 1;
        }
        // Fill it with 0 when all check fails
        else
        {
          S[count][j] = 100;
        } 
      }
      // Count 1° iteration
      else
      {
        // Check col == solution value
        if (j == row)
        {
          // Restoring proper value 
          S[count][j] = row + 1;
        } 
      }
    }

    // Lj update
    for (j = 1; j < n; j++) 
    {
      // Count next iterations 
      if (count != 0)
      {
        // Check if previous value to compare isn't 0
        if (Lj[count - 1][j] != 100)
        {
          // If the new value is less
          // and j isn't already inside S
          // the previous value is replaced with the new one
          if (G[row][j] + old_min < Lj[count - 1][j] && selected[j] == false)
          {
            Lj[count][j] = G[row][j] + old_min;
          } 
          // Previous value remains
          else
          {
            Lj[count][j] = Lj[count - 1][j];
          }
        }
        else if (Lj[count - 1][j] == 100)
        {
          if (G[row][j] == 100)
          {
            Lj[count][j] = G[row][j];
          }
          else 
          {
            Lj[count][j] = G[row][j] + old_min;
          }
        }
      }
      else
      {
        // Count 1° iteration
        // Copying first row from G to Lj
        Lj[0][j] = G[0][j];
      }
    }

    for (j = 1; j < n; j++) 
    {
      // Count next iterations 
      if (count != 0)
      {
        // Check if previous value to compare isn't 0
        if (Pj[count - 1][j] != 100)
        {
          // If the new value is less
          // and j isn't already inside S
          // the previous value is replaced with the new one
          if (G[row][j] + old_min < Lj[count - 1][j] && selected[j] == false)
          {
            Pj[count][j] = row + 1;
          } 
          // Previous value remains
          else
          {
            Pj[count][j] = Pj[count - 1][j];
          }
        }
        else if (Pj[count - 1][j] == 100)
        {
          // Setting pj row
          if (G[row][j] != 100) 
          {
            Pj[count][j] = row + 1;
          }
          else 
          {
            Pj[count][j] = 100;
          }
        }
      }
      else
      {
        // Count 1° iteration
        // Filling Pj first row
        if (G[0][j] != 100)
        {
          Pj[0][j] = 1;
        }
        else 
        {
          Pj[0][j] = 100;
        }
      }
    }

    // Old min reset
    old_min = 100;

    // Min search
    for (j = 1; j < n; j++)
    {
      // Checks: 
      // Lj value not 0
      // Lj row wasn't already searched
      // Lj Lj[count][j];value is smaller than min
      if (Lj[count][j] != 100 && selected[j] == false && Lj[count][j] < min) 
      {
        // New min value
        min = Lj[count][j];
        // Saving min for shorter path algo 
        old_min = Lj[count][j];        
        // Saving index
        tmp_row = j;
      }

    }

    // Row update
    row = tmp_row;

    // Selected state update
    selected[row] = true;
        
    // Min reset
    min = 100;
  }
    

}


void graph::print()
{
    cout<<"\n\n------- G: -------\n\n";

    for (i = 0; i < n; i++)
    {
      cout<<"|";

      for (j = 0; j < n; j++)
      {
        if (G[i][j] == 100)
        {
          cout<<"  -";  
        }
        else
        { 
          if (G[i][j] >= 10)
          {
            cout<<" "<<G[i][j];  
          }
          else
          {
            cout<<"  "<<G[i][j];
          }
        }
      }
      
      cout<<"|\n";
    }

    cout<<"\n\n------- S: -------\n\n";

    for (i = 0; i < n; i++)
    {
      cout<<"|";

      for (j = 0; j < n; j++)
      {
        if (S[i][j] == 100)
        {
          cout<<"  -";  
        }
        else
        { 
          if (S[i][j] >= 10)
          {
            cout<<" "<<S[i][j];  
          }
          else
          {
            cout<<"  "<<S[i][j];
          }
        }
      }
      
      cout<<"|\n";
    }

    cout<<"\n\n------- Lj: -------\n\n";

    for (i = 0; i < n; i++)
    {
      cout<<"|";

      for (j = 1; j < n; j++)
      {
        if (Lj[i][j] == 100)
        {
          cout<<"  -";  
        }
        else
        {
          if (Lj[i][j] >= 10)
          {
            cout<<" "<<Lj[i][j];
          }
          else
          {
            cout<<"  "<<Lj[i][j];
          }
        }
      }

      cout<<"|\n";
    }

    cout<<"\n\n------- Pj: -------\n\n";

    for (i = 0; i < n; i++)
    {
      cout<<"|";

      for (j = 1; j < n; j++)
      {
        if (Pj[i][j] == 100)
        {
          cout<<"  -";  
        }
        else
        {
          if (Pj[i][j] >= 10)
          {
            cout<<" "<<Pj[i][j];
          }
          else
          {
            cout<<"  "<<Pj[i][j];
          }
        }
      }

      cout<<"|\n";
    }
}

int main()
{
  graph graph;
  graph.get_data();
  graph.mst();
  graph.print();
  return 0;
}
   

