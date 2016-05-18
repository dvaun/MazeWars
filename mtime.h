#ifndef MTIME_H
#define MTIME_H
double timeDiff(struct timespec *start, struct timespec *end);

void timeCopy(struct timespec *dest, struct timespec *source);
#endif
