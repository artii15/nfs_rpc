/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "nfs.h"

int *
ropen_1_svc(struct OpenRequest *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *
rcreat_1_svc(struct CreatRequest *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

struct ReadResponse *
rread_1_svc(struct FileAccessRequest *argp, struct svc_req *rqstp)
{
	static struct ReadResponse  result;

	/*
	 * insert server code here
	 */

	return &result;
}

ssize_t *
rwrite_1_svc(struct FileAccessRequest *argp, struct svc_req *rqstp)
{
	static ssize_t  result;

	/*
	 * insert server code here
	 */

	return &result;
}