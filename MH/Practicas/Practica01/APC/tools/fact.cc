/*
 *Para ver que tarde usamos un clásico lento, factorial.
 */
int fact(int n) {
  if (n <= 1) {
    return 1;
  } else {
    return fact(n - 1) + fact(n - 2);
  }
}
