#include <mpi.h>
#include "StGermain/StGermain.h"
#include "StGermain/FD/FD.h"
#include "Snac/Snac.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bmi.h>


int
main (void)
{
    BMI_Model *self = NULL;
    int err = BMI_SUCCESS;
    char name[BMI_MAX_COMPONENT_NAME];
    //char *inputs[BMI_INPUT_VAR_NAME_COUNT];
    char **inputs;
    
    /***********************/
    /* Initialization      */
    /***********************/
    fprintf (stdout, "Initializing... ");
    
    err = BMI_Initialize ("./bmi_test.xml", &self);
    if (err || !self)
        return EXIT_FAILURE;
    
    fprintf (stdout, "PASS\n");

    /***********************/
    /* Get component name  */
    /***********************/

    BMI_Get_component_name (self, name);
    fprintf (stdout, "%s\n", name);

    /*********************************/
    /* Print input var names (testing) */
    /*********************************/
    {
        int i;
        int count;
        BMI_Get_input_var_name_count( self, &count );
        fprintf (stdout, "input var count: %d\n", count);
        //for (i = 0; i<BMI_INPUT_VAR_NAME_COUNT; i++)
        inputs = malloc (sizeof(inputs) * count);
        for (i = 0; i<count; i++)
            inputs[i] = (char*) malloc (sizeof (char) * BMI_MAX_VAR_NAME);
        BMI_Get_input_var_names (self, inputs);

        for (i = 0; i<count; i++)
            free(inputs[i]);
        free(inputs);
    }

    /***********************/
    /* Update              */
    /***********************/
    // BMI_Run_model (self);

    {
        int i;
        const int n_steps = 10;
        const double end_time = 3.1536e7*19.5; /* 19.5 years. */
        double time;
        
        fprintf (stdout, "\n\nRunning until %d steps...\n", n_steps);
        for (i = 0; i < n_steps; i++)
            {
                if (BMI_Update (self)!=0)
                    return EXIT_FAILURE;
            }
        
        fprintf (stdout, "\n\nRunning until t = %.4e (=%f years)...\n", end_time, end_time/3.1536e7);
        if (BMI_Update_until (self, end_time)==0  && BMI_Get_current_time (self, &time)==0) {
            if (fabs (time-end_time) < 1e-6)
                fprintf (stdout, "PASS\n");
            else {
                fprintf (stdout, "%f (= %f years)\n", time, time/3.1536e7);
                return EXIT_FAILURE;
            }
        }
        else
            return EXIT_FAILURE;
    }
    
    /***********************/
    /* Finalization        */
    /***********************/
    fprintf (stdout, "\n\nFinalizing... ");

    
    err = BMI_Finalize (self);
    
    if (err)
        return EXIT_FAILURE;
    fprintf (stdout, "PASS\n");
    
    return EXIT_SUCCESS;
}
