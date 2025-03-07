! we are calculating the root of
! 3x + cos x + 1 = 0
! using 3 methods:
! iterative method,
! newton's method,
! secant method.

program lab1_3
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp) :: x0, x1, x2, f0, f1
    real(kind=dp), parameter :: EPS = 10e-7, PI = DACOS(-1.D0), x_start = PI / (-8.0_dp)
    integer :: n_approx, n_actual
    real(kind=dp) :: q, m, delta

    q = 1.0_dp/3_dp
    m = 1.0_dp/4_dp
    delta = PI/8_dp

    n_approx = int(log(EPS * (1_dp - q) / m) / log(q))
    print *, 'Approximate number of iterations: ', n_approx
    print '(A)', "=========================================="

    ! iterational method
    print *, 'Iterational method'
    x0 = x_start
    n_actual = 0
    do
        n_actual = n_actual + 1
        x1 = phi(x0)
        if (abs(x1 - x0) <= EPS) exit
!        print '(A, ES11.4)', ' closing in at ', abs(x1 - x0)
        x0 = x1
    enddo
    print *, 'The number of iterations: ', n_actual
    print '(A, ES11.4)', ' The discrepancy:  ', f(x1)
    print '(A, F14.11)', ' Approximated root ', x1
    print '(A)', "=========================================="
    

    ! newton's method
    print *, "Newton's method"
    x0 = x_start
    n_actual = 0
    do
        n_actual = n_actual + 1
        x1 = x0 - f(x0)/dfdx(x0)
        if (abs(x1 - x0) <= EPS) exit
!       print '(A, ES11.4)', ' closing in at ', abs(x1 - x0)
        x0 = x1
    enddo
    print *, 'The number of iterations: ', n_actual
    print '(A, ES11.4)', ' The discrepancy:  ', f(x1)
    print '(A, F14.11)', ' Approximated root ', x1
    print '(A)', "=========================================="

    ! secant method
    print *, 'Secant method'
    x0 = x_start
    x1 = x0 - f(x0)/dfdx(x0)
    f0 = f(x0)
    n_actual = 1
    do
        n_actual = n_actual + 1

        f1 = f(x1)
        x2 = x1 - f1 * (x1 - x0)/(f1 - f0)

        if (abs(x2 - x1) <= EPS) exit
        if (n_actual >= 10) exit
!       print '(A, ES11.4)', ' closing in at ', abs(x2 - x1)
        f0 = f1
        x0 = x1
        x1 = x2
    enddo
    print *, 'The number of iterations: ', n_actual
    print '(A, ES11.4)', ' The discrepancy:  ', f(x2)
    print '(A, F14.11)', ' Approximated root ', x2

contains
    real(kind=dp) function phi(x)
        implicit none
        real(kind=dp), intent(in) :: x
        phi = (cos(x) + 1.0_dp) / (-3.0_dp)
    end function phi

    real(kind=dp) function f(x)
        implicit none
        real(kind=dp), intent(in) :: x
        f = 3*x + cos(x) + 1.0_dp
    end function f

    real(kind=dp) function dfdx(x)
        implicit none
        real(kind=dp), intent(in) :: x
        dfdx = 3 - sin(x)
    end function dfdx
end program lab1_3
