

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true if
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */

// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    const int nDays, const int kPossibleWorkers,
    //int availRow, int availCol,
    int schedRow, int schedCol,
    std::vector<int>& numShifts);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    //if there's nothing in the matrix, return false
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int nDays=avail.size(); //rows OR number of days
    int kPossibleWorkers=avail[0].size(); //cols OR possible workers 


    //initialize all values of sched to 0
    for(int i=0; i<nDays; i++)
    {
        std::vector<Worker_T> loop(dailyNeed, INVALID_ID);
        sched.push_back(loop);

    }

    std::vector<int> numShifts(kPossibleWorkers, 0);
    
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, nDays, kPossibleWorkers,
                         0, 0, numShifts);

}

bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    const int nDays, const int kPossibleWorkers,
    //int availRow, int availCol,
    int schedRow, int schedCol,
    std::vector<int>& numShifts)
{
    //avail(input): nDays=rows, kPossibleWorkers=cols
    //sched(output): nDays=rows, dailyNeed=cols

    //base case: check if row is equal to days, if so return true
    //else base case 2: check if col is equal to dailyNeed, if so return schedHelper for next day
    
    //we we are at the end of output (sched)

    //UPDATE BASE CASE TO FIT FIRST
    //go through all people available for the day
    if(schedRow==nDays)
    {
        return true;
    }
    if(schedCol==dailyNeed)
    {
        if(scheduleHelper(avail, dailyNeed, maxShifts, sched, nDays, kPossibleWorkers,
            schedRow+1, 0, numShifts))
            {
              return true;
            } 
        else return false;

    }

    for(int i=0; i<kPossibleWorkers; i++)
    {
        //if the person is available, has more shifts, is currently not in same day
        //then add to schedule
        if(avail[schedRow][i]==1 && numShifts[i]<maxShifts)
            //std::find(sched[schedRow].begin(), sched[schedRow].end(), i) == sched[schedRow].end())
        {
            sched[schedRow][schedCol]=i;
            numShifts[i]++;
            bool status=0;
            
            //Here instead check if schedHelper for the next COL is true, if so return true. (Do not return false yet)

            //SEND THIS UP TO SECOND BASE CASE

            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, nDays, kPossibleWorkers,
                schedRow, schedCol+1, numShifts))
            {
              return true;
            }

            
            sched[schedRow][schedCol]=INVALID_ID;
            numShifts[i]--;
            
        }
    }

    return false;




    // if(schedRow>=nDays-1 && schedCol>=dailyNeed-1)
    // {
    //     return true;
    // }
    // //go through all people available for the day
    // for(int i=0; i<kPossibleWorkers; i++)
    // {
    //     //if the person is available, has more shifts, is currently not in same day
    //     //then add to schedule
    //     if(avail[schedRow][i]==1 && numShifts[i]<maxShifts)
    //         //std::find(sched[schedRow].begin(), sched[schedRow].end(), i) == sched[schedRow].end())
    //     {
    //         sched[schedRow][schedCol]=i;
    //         numShifts[i]++;
    //         bool status=0;
            
    //         if(schedCol>=dailyNeed-1)
    //         {
    //             if(scheduleHelper(avail, dailyNeed, maxShifts, sched, nDays, kPossibleWorkers,
    //                 schedRow+1, 0, numShifts)){
    //                   return true;
    //                 } else return false;

    //         }
    //         else
    //         {
    //             if(scheduleHelper(avail, dailyNeed, maxShifts, sched, nDays, kPossibleWorkers,
    //                 schedRow, schedCol+1, numShifts)){
    //                   return true;
    //                 }

    //         }
            
    //     }
        // sched[schedRow][schedCol]=INVALID_ID;
        // numShifts[i]--;
    // }

    // return false;
}

