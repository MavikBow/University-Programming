! we work with the equation f(x) = (1 - x**5) / 3
!
! n is the number of iterations

program IntergralEq
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:), allocatable :: t, x0, x1, x_precise, y
    real(kind=dp) :: alpha, n_calculated, lambda_0, h, temp
    real(kind=dp), parameter :: Eps = 0.001_dp
    integer :: i, n_approximated, n_actual, m

    ! initiating variables

    h = 0.05_dp
    m = int(1.0_dp / h)
    lambda_0 = 2.0_dp / 3.0_dp

    allocate(t(m + 1))
    allocate(x0(m + 1))
    allocate(x1(m + 1))
    allocate(x_precise(m + 1))
    allocate(y(m + 1))

    t(1) = 0.0_dp
    do i = 2, m + 1
        t(i) = t(i-1) + h
    end do 
    print '(A)', 'the vector t'
    print '(F14.2)', t

    ! the precise x calculation 
    x_precise = 4.0_dp * lambda_0 / (5.0_dp * (4.0_dp - lambda_0)) * t**2 + t**3

    print '(A)', 'the precise x'
    print '(F14.5)', x_precise

    ! the algorithm starts in C[0,1]

    alpha = abs(lambda_0) / 2.0_dp
    print '(A)', 'the contraction coefficient alpha in C[0,1]'
    print '(F14.5)', alpha 

    n_calculated = log((2.0_dp * Eps)/(2.0_dp - abs(lambda_0))) / log(alpha)
    print '(A)', 'the calculated number of iterations in C[0,1]'       
    print '(F14.5)', n_calculated

    n_approximated = int(n_calculated) + 1
    print '(A)', 'the approximate number of iterations in C[0,1]' 
    print *, n_approximated

    n_actual = 0
    x0 = 0.0_dp
    do 
        temp = dot_product(t, x0)
        do i = 1, size(t, 1)
            x1(i) = lambda_0 * h * t(i)**2 * temp + t(i)**3
        end do
        n_actual = n_actual + 1
        if (maxval(abs(x0-x1)) < Eps) exit
        x0 = x1
    end do

    print '(A)', 'the actual number of iterations in C[0,1]'
    print *, n_actual

    print '(A)', 'the last iteration in C[0,1]'
    print '(F14.5)', x1

    print '(A)', 'posterior error in C[0,1]'
    print '(F14.5)', maxval(abs(x1 - x_precise))

    ! the algorithm starts in L_2[0,1]

    alpha = abs(lambda_0) / sqrt(15.0_dp)
    print '(A)', 'the contraction coefficient alpha in L_2[0,1]'       
    print '(F14.5)', alpha 

    n_calculated = log(sqrt(7.0_dp) * Eps * (1.0_dp - alpha)) / log(alpha)
    print '(A)', 'the calculated number of iterations in L_2[0,1]'       
    print '(F14.5)', n_calculated

    n_approximated = int(n_calculated) + 1
    print '(A)', 'the approximate number of iterations in L_2[0,1]' 
    print *, n_approximated

    n_actual = 0
    x0 = 0.0_dp
    do 
        temp = dot_product(t, x0)
        do i = 1, size(t, 1)
            x1(i) = lambda_0 * h * t(i)**2 * temp + t(i)**3
        end do
        n_actual = n_actual + 1

        y = abs(x0 - x1)
        if (sqrt(h * dot_product(y,y)) < Eps) exit
        x0 = x1
    end do

    print '(A)', 'the actual number of iterations in L_2[0,1]'
    print *, n_actual

    print '(A)', 'the last iteration in L_2[0,1]'
    print '(F14.5)', x1
 
    print '(A)', 'posterior error in L_2[0,1]'
    y = x1 - x_precise
    print '(F14.5)', sqrt(h * dot_product(y,y))

    print '(A)', 'final vector t           x1         x_precise'
    do i = 1, size(t,1)
        print '(3(F14.5, 1X))', t(i), x1(i), x_precise(i)
    end do

    deallocate(t)
    deallocate(x0)
    deallocate(x1)
    deallocate(x_precise)
    deallocate(y)
end program IntergralEq
