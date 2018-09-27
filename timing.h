/*#ifndef TIMING_H
#define TIMING_H

#include <chrono>

//------------------------------------------------------------------------------
// Record the execution time of some code, in milliseconds.
// eg:
//	DECLARE_TIMING(myTimer);
//	START_TIMING(myTimer);
//	  printf("A slow calc = %f\n", 1.0/sqrt(2.0) );
//	STOP_TIMING(myTimer);
//	SHOW_TIMING(myTimer, "My Timer");
//------------------------------------------------------------------------------
#define DECLARE_TIMING(s)	    	std::chrono::high_resolution_clock::time_point timeStart_##s; std::chrono::high_resolution_clock::time_point timeDiff_##s; std::chrono::high_resolution_clock::time_point timeTally_##s = std::chrono::duration::zero(); long long countTally_##s = 0
#define START_TIMING(s)		    	timeStart_##s = now();
#define STOP_TIMING(s)		    	timeDiff_##s = (long long)(now() - timeStart_##s); timeTally_##s += timeDiff_##s; countTally_##s++
#define GET_TIMING(s)		    	(long long)(std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count())
#define GET_AVERAGE_TIMING(s)		(double)(countTally_##s ? 0.001 * ( (double)timeTally_##s / ((double)countTally_##s * cvGetTickFrequency()) ) : 0)
#define GET_TIMING_COUNT(s)  		(int)(countTally_##s)
#define GET_TOTAL_TIMING(s)			(double)(0.001 * ( (double)timeTally_##s / (double)cvGetTickFrequency() ))
#define CLEAR_AVERAGE_TIMING(s)		timeTally_##s = 0; countTally_##s = 0
#define SHOW_SHORT_TIMING(s, msg)	printf("%s \t %.1fms (%.2fmin).\n", msg, GET_TIMING(s), GET_TIMING(s)/60000)
#define SHOW_TIMING(s, msg)	    	printf("%s time: \t %dms (%.1fmin) \t (%.2fms (%.1fmin) average across %d runs).\n", msg, cvRound(GET_TOTAL_TIMING(s)), GET_TOTAL_TIMING(s)/60000, GET_AVERAGE_TIMING(s), GET_AVERAGE_TIMING(s)/60000, GET_TIMING_COUNT(s) )
#define SHOW_SHORT_TIMING_OS(s, msg, out_stream)	out_stream << msg << '\t' << GET_TIMING(s) << "ms (" << std::floorf((GET_TOTAL_TIMING(s)/60000)*100)/100 << "min).\n"
#define SHOW_TIMING_OS(s, msg, out_stream)	    	out_stream << msg << " time:\t" << std::ceilf(GET_TOTAL_TIMING(s)) << "ms (" << std::floorf((GET_TOTAL_TIMING(s)/60000)*100)/100 << "min)\t(" << std::ceilf(GET_AVERAGE_TIMING(s)*100)/100 << "ms (" << std::floorf((GET_AVERAGE_TIMING(s)/60000)*100)/100 << "min) average across " << GET_TIMING_COUNT(s) << " runs).\n"

#define SHOW_TIMING_(s, msg)	    printf("%s time: \t %dms.\n", msg, cvRound(GET_TIMING(s)) )

#define GET_TOTAL_TIMING(s)         (double)(0.001 * ( (double)timeTally_##s / (double)cvGetTickFrequency() ))
#define SHOW_TOTAL_TIMING(s, msg)	printf("%s total time: \t %dms (%.1fmin) across %d runs).\n", msg, cvRound(GET_TOTAL_TIMING(s)), GET_TOTAL_TIMING(s)/60000, GET_TIMING_COUNT(s) )
#define FILE_TOTAL_TIMING(s,msg,f)  f << msg <<  "total time: \t " << cvRound(GET_TOTAL_TIMING(s)) << "ms across " << GET_TIMING_COUNT(s) << " runs.";
#endif*/

#ifndef TIMING_H
#define TIMING_H

//------------------------------------------------------------------------------
// Record the execution time of some code, in milliseconds.
// eg:
//	DECLARE_TIMING(myTimer);
//	START_TIMING(myTimer);
//	  printf("A slow calc = %f\n", 1.0/sqrt(2.0) );
//	STOP_TIMING(myTimer);
//	SHOW_TIMING(myTimer, "My Timer");
//------------------------------------------------------------------------------
#define DECLARE_TIMING(s)	    	long long timeStart_##s = 0; long long timeDiff_##s = 0; long long timeTally_##s = 0; long long countTally_##s = 0
#define START_TIMING(s)		    	timeStart_##s = cvGetTickCount()
#define STOP_TIMING(s)		    	timeDiff_##s = (cvGetTickCount() - timeStart_##s); timeTally_##s += timeDiff_##s; countTally_##s++
#define GET_TIMING(s)		    	(double)(0.001 * ( (double)timeDiff_##s / (double)cvGetTickFrequency() ))
#define GET_AVERAGE_TIMING(s)		(double)(countTally_##s ? 0.001 * ( (double)timeTally_##s / ((double)countTally_##s * cvGetTickFrequency()) ) : 0)
#define GET_TIMING_COUNT(s)  		(int)(countTally_##s)
#define GET_TOTAL_TIMING(s)			(double)(0.001 * ( (double)timeTally_##s / (double)cvGetTickFrequency() ))
#define CLEAR_AVERAGE_TIMING(s)		timeTally_##s = 0; countTally_##s = 0
#define SHOW_SHORT_TIMING(s, msg)	printf("%s \t %.1fms (%.2fmin).\n", msg, GET_TIMING(s), GET_TIMING(s)/60000)
#define SHOW_TIMING(s, msg)	    	printf("%s time: \t %dms (%.1fmin) \t (%.2fms (%.1fmin) average across %d runs).\n", msg, cvRound(GET_TOTAL_TIMING(s)), GET_TOTAL_TIMING(s)/60000, GET_AVERAGE_TIMING(s), GET_AVERAGE_TIMING(s)/60000, GET_TIMING_COUNT(s) )
#define SHOW_SHORT_TIMING_OS(s, msg, out_stream)	out_stream << msg << '\t' << GET_TIMING(s) << "ms (" << std::floorf((GET_TOTAL_TIMING(s)/60000)*100)/100 << "min).\n"
#define SHOW_TIMING_OS(s, msg, out_stream)	    	out_stream << msg << " time:\t" << std::ceilf(GET_TOTAL_TIMING(s)) << "ms (" << std::floorf((GET_TOTAL_TIMING(s)/60000)*100)/100 << "min)\t(" << std::ceilf(GET_AVERAGE_TIMING(s)*100)/100 << "ms (" << std::floorf((GET_AVERAGE_TIMING(s)/60000)*100)/100 << "min) average across " << GET_TIMING_COUNT(s) << " runs).\n"

#define SHOW_TIMING_(s, msg)	    printf("%s time: \t %dms.\n", msg, cvRound(GET_TIMING(s)) )

#define GET_TOTAL_TIMING(s)         (double)(0.001 * ( (double)timeTally_##s / (double)cvGetTickFrequency() ))
#define SHOW_TOTAL_TIMING(s, msg)	printf("%s total time: \t %dms (%.1fmin) across %d runs).\n", msg, cvRound(GET_TOTAL_TIMING(s)), GET_TOTAL_TIMING(s)/60000, GET_TIMING_COUNT(s) )
#define FILE_TOTAL_TIMING(s,msg,f)  f << msg <<  "total time: \t " << cvRound(GET_TOTAL_TIMING(s)) << "ms across " << GET_TIMING_COUNT(s) << " runs.";
#endif