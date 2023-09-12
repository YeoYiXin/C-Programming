//Student's Name: Yeo Yi Xin
//Student's ID: 20414841
//Assignment Question 3

#include <stdio.h> //include standard input output library
#include <stdlib.h> //include standard library
int main (void) //start main function
{
    int worker_job=0, working_day=0, packed_item=0;//in number
    float manager_salary=0,dailyworker_salary=0, overtime_hour=0, hourlyworker_salary=0;
    float working_hours=0, commissionworker_salary=0, a=0, b=0, c=0, d=0,e=0, laboursalary=0;
    char choice, choice2;
    printf("Worker Salary Calculator");
    printf("\n------------------------------------\n");
    printf("\nShould we start now (Y/N)? ");
    scanf(" %c", &choice);
    while (choice!='y' && choice!='Y' && choice!='N' && choice!='n') //start while loop
    {
        printf("\nNO SUCH CHOICE. Would you still like to continue?");
        scanf(" %c", &choice);
    } //end while loop
    if (choice=='N' || choice=='n') //start if condition
    {
        printf("\nThank you. See you next time!");
        return 0;
    } //end if condition
    while (choice=='y' || choice=='Y')
    {
        system("CLS");
        printf("\n\n Employee code:\n 1. Manager\n 2. Daily worker\n 3. Hourly worker");
        printf("\n 4. Commission worker\n 5. Labour at product packing");
        printf("\nPlease put in the employee code as shown above: ");
        scanf("%d", &worker_job);
        switch(worker_job) //starting of switch statement
        {
        case 1: //manager
            {
                printf("\nEmployee code: 1");
                printf("\nWork position: Manager");
                printf("\nDescription: This position receives a fixed salary");
                printf("\nType in your monthly salary (can have decimal points): ");
                scanf(" %f", &manager_salary);
                while (manager_salary<=0 || manager_salary > 30000) //start while loop
                {
                    if (manager_salary<=0) //start if condition
                    {
                        printf("\nYou have put in a negative value. Please try again");
                        printf("\nType in your monthly salary (can have decimal points): ");
                        scanf(" %f", &manager_salary);
                    } //end if condition
                    if (manager_salary > 30000) //start if condition
                    {
                        printf("The salary is too large for a manager! Please try again");
                        printf("\nType in your monthly salary (can have decimal points): ");
                        scanf(" %f", &manager_salary);
                    }//end if condition
                }//end while loop
                printf("Your salary is $%.2f", manager_salary);
                break; //stop case 1
            }//end case 1

        case 2: //Daily worker
            {
                printf("\nEmployee code: 2");
                printf("\nWork position: Daily worker");
                printf("\nDescription: This position can receive overtime salary (which is 2/3 of daily wages) for each extra day");
                printf("\nType in your basic monthly salary (can have decimal points): ");
                scanf(" %f", &dailyworker_salary);
                while (dailyworker_salary<=0 || dailyworker_salary > 10000) //start while loop
                {
                    if (dailyworker_salary<=0) //start if condition
                    {
                        printf("\nYou have put in a negative value. Please try again");
                        printf("\nType in your basic monthly salary (can have decimal points): ");
                        scanf(" %f", &dailyworker_salary);
                    } //end if condition
                    if (dailyworker_salary > 10000) //start if condition
                    {
                        printf("The salary is too large for a daily worker! Please try again");
                        printf("\nType in your basic monthly salary (can have decimal points): ");
                        scanf(" %f", &dailyworker_salary);
                    }//end if condition
                }//end while loop
                printf("\nHow many days have you worked for this week (0-7)? ");
                scanf(" %d", &working_day);
                while (working_day>7 || working_day <0) //start while loop
                {
                    printf("\nThe input you type in is not logic. The value you put should not be a negative value.");
                    printf("\nOther than that, you can only work at most days a week. The 7th day is the extra day. ");
                    printf("\nSo, how many days have you worked for this week (0-6)? ");
                    scanf(" %d", &working_day);
                } //end while loop
                if (working_day==7)
                {
                    a=working_day*4; //counting the working day in a month by considering there are 4 weeks in a month
                    b=dailyworker_salary/a; //counting the one-day salary of a daily worker
                    c=b*2/3; //counting the overtime rate for each day
                    printf("\nConsidering there are 4 weeks in a month and each week, you work the same number of working day;.");
                    d=c*4;
                    printf("\nOvertime pay for the whole month = $ %.2f", d);
                    dailyworker_salary=d+dailyworker_salary;
                    printf("\nYour salary is $ %.2f", dailyworker_salary);
                }
                else
                {
                    printf("\nYour salary is $ %.2f", dailyworker_salary);
                }
                break;
            } //end case 2

        case 3: //Hourly worker
            {
                printf("\nEmployee code: 3");
                printf("\nWork position: Hourly worker");
                printf("\nDescription: This position can work 50 hours in a week and half of hourly wage for overtime.");
                printf("\nType in your hourly wage (can have decimal points): ");
                scanf(" %f", &hourlyworker_salary);
                while (hourlyworker_salary<=0 || hourlyworker_salary > 100) //start while loop
                {
                    if (hourlyworker_salary<=0) //start if condition
                    {
                        printf("\nYou have put in a negative value. Please try again");
                        printf("\nType in your hourly wage (can have decimal points): ");
                        scanf(" %f", &hourlyworker_salary);
                    } //end if condition
                    if (hourlyworker_salary > 100) //start if condition
                    {
                        printf("The salary is too large for an hourly worker! Please try again");
                        printf("\nType in your hourly wage (can have decimal points): ");
                        scanf(" %f", &hourlyworker_salary);
                    }//end if condition
                }//end while loop
                printf("\nConsidering there are 4 weeks in a month and each week, you work the same amount of hour ");
                printf("\nHow many hours have you worked in one week? ");
                scanf(" %f", &working_hours);
                while (working_hours<0) //start while loop
                {
                    printf("\nNO NEGATIVE VALUE");
                    printf("\nSo, how many hours have you worked for this week? ");
                    scanf(" %f", &working_hours);
                } //end while loop
                if (working_hours>50) //start if condition
                {
                    a=50*hourlyworker_salary;
                    b=(working_hours-50)*(hourlyworker_salary/2); //salary for overtime
                    c=b*4;
                    d=a+b; //total salary for that one week
                    hourlyworker_salary=d*4; //considering each week, the worker works for the same amount of hours
                    printf("\nOvertime pay for one month = $ %.2f", c);
                    printf("\nYour salary is $ %.2f", hourlyworker_salary);
                } //end if condition
                else //start else if condition - working hours <50 || working hours==50
                {
                    a=working_hours*hourlyworker_salary;
                    hourlyworker_salary=a*4;
                    printf("\nYour salary is $ %.2f", hourlyworker_salary);
                } //end else if condition
                break;
            } //end case 3

        case 4: //Commission worker
            {
                printf("\nEmployee code: 4");
                printf("\nWork position: Commission worker");
                printf("\nDescription: This position have weekly wages of $230 + 5.9%% for total sale in a week.");
                printf("\nType in your total sale for this week (can have decimal points): ");
                scanf(" %f", &commissionworker_salary);
                while (commissionworker_salary<=0 || commissionworker_salary > 10000) //start while loop
                {
                    if (commissionworker_salary<=0) //start if condition
                    {
                        printf("\nYou have put in a negative value. Please try again");
                        printf("\nType in your total sale for this week (can have decimal points): ");
                        scanf(" %f", &commissionworker_salary);
                    } //end if condition
                    if (commissionworker_salary > 10000) //start if condition
                    {
                        printf("The sale is too large for only a week! Please try again");
                        printf("\nType in your total sale for this week (can have decimal points): ");
                        scanf(" %f", &commissionworker_salary);
                    }//end if condition
                }//end while loop
                printf("\nConsidering there are 4 weeks in a month and each week, your total sale for every week is the same.");
                a=commissionworker_salary*0.059; //5.9% == 0.059
                b=a*4; //total commission in 4 weeks
                commissionworker_salary=(230*4)+b;
                printf("\nThis month commission is $ %.2f", b);
                printf("\nYour salary is $ %.2f", commissionworker_salary);
                break;
            } //end case 4

        case 5: //Labour at product packing
            {
                //(5) labour at product packing: 0.05% of total sum of total item packed in a week.
                printf("\nEmployee code: 5");
                printf("\nWork position: Labour at product packing");
                printf("\nDescription: This position earn 0.05%% of total sum of total item packed in a week.");
                printf("\nType in your total sum of total item packed for this week: ");
                scanf(" %d", &packed_item);
                while (packed_item<=0 || packed_item > 1000000) //start while loop
                {
                    if (packed_item<=0) //start if condition
                    {
                        printf("\nYou have put in a negative value. Please try again");
                        printf("\nType in your total sum of total item packed for this week: ");
                        scanf(" %d", &packed_item);
                    } //end if condition
                    if (packed_item > 1000000) //start if condition
                    {
                        printf("The packed item is too large for only a week! Please try again");
                        printf("\nType in your total sum of total item packed for this week: ");
                        scanf(" %d", &packed_item);
                    }//end if condition
                }//end while loop
                printf("\nConsidering there are 4 weeks in a month and each week,");
                printf("your total packed item for a week is the same.");
                a=packed_item*0.0005; //0.05% is 0.05/100=0.0005
                laboursalary=a*4;
                printf("\nYour salary is $ %.2f", laboursalary);
                break;
            }//end case 5

        default: printf("\nNo such choices. Please try again.\n"); break;
        }//end switch statement

        printf("\nWould you like to calculate salary again?");
        scanf(" %c", &choice2);
        if (choice2=='N' || choice2=='n') //end if condition
        {
            printf("\nThank you. See you next time!");
            break;
        }//end if condition
    }
    return 0; //tell the compiler it has successfully compiled everything.
}//end main function
