program lab2
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    double precision, allocatable :: x(:), A(:,:)
    double precision, parameter :: alpha_j = 0.3_dp
    double precision :: x_s, x_ss, x_sss, temp
    integer, parameter :: n = 10
    integer :: i, j

    allocate(x(n + 1))
    allocate(A(6, 7))
    
    do i = 0, n
        x(i + 1) = alpha_j + dble(i) / dble(n)
    enddo

    x_s = x(1) + dble(2) / dble(30)
    x_ss = x(6) + dble(1) / dble(20)
    x_sss = x(10) - dble(1) / dble(30)

    do i = 1, 6
    do j = 1, 6
        A(i,j) = phil_phik(x, i-1, j-1)
    enddo
        A(i, 7) = f_phil(x, i-1)
    enddo

    call gauss(A)

!   print *, 'matrix A'
!   do i = 1, 6
!       print '(7(F10.5, 1X))', (A(i,j), j = 1, 7)
!   end do

    print '(A)', "x(i)    f(x)    phi(x)"
    do i = 0, n
        print '(F4.2, F14.11, F14.11)', x(i+1), f_real(x(i+1)), phi_real(A(:,7), x(i+1))
    enddo

    ! discrepancy
    temp = 0
    do i = 0, n
        temp = temp + (phi_real(A(:,7), x(i+1)) - f_real(x(i+1))) ** 2
    enddo
    temp = sqrt(temp)

    print '(A, ES11.4)', ' The overall discrepancy:  ', temp
    print '(A)', 'other 3 discrepancies:  '
    print '(ES11.4)', phi_real(A(:,7), x_s) - f_real(x_s)
    print '(ES11.4)', phi_real(A(:,7), x_ss) - f_real(x_ss)
    print '(ES11.4)', phi_real(A(:,7), x_sss) - f_real(x_sss)

    deallocate(x)
    deallocate(A)

contains

! for MHK

    double precision function f_real(x_i)
        implicit none
        double precision, intent(in) :: x_i
        f_real = alpha_j * EXP(-x_i) + (1_dp - alpha_j) * sin(x_i)
    end function f_real

    double precision function phil_phik(x, l, k)
        implicit none
        double precision, dimension(:), intent(in) :: x
        integer, intent(in) :: l, k
        integer :: i
        phil_phik = 0
        do i = 1, size(x)
           phil_phik = phil_phik + x(i) ** (k + l)
        enddo
    end function phil_phik

    double precision function f_phil(x, l)
        implicit none
        double precision, dimension(:), intent(in) :: x
        integer, intent(in) :: l
        integer :: i
        f_phil = 0
        do i = 1, size(x)
           f_phil = f_phil + f_real(x(i)) * x(i) ** l
        enddo
    end function f_phil

    subroutine gauss(A)
        implicit none
        double precision, dimension(:,:), intent(inout) :: A
        integer :: i, j, n
        n = size(A,1) ! number of rows
        ! forward elimination
        do i = 1, n
            A(i, i + 1 :) = A(i, i + 1 :) / A(i,i)
            do concurrent (j = i + 1 : n)
                A(j, i:) = A(j, i:) - A(j,i) * A(i, i:)
            end do
        end do
        ! back substitution
        do j = n, 1, -1
            do concurrent (i = 1 : j - 1) 
                A(i, n + 1 :) = A(i, n + 1 :) - A(i,j) * A(j, n + 1 :)
            end do
        end do
    end subroutine

    double precision function phi_real(c, x_i)
        implicit none
        double precision, dimension(:), intent(in) :: c
        double precision, intent(in) :: x_i
        integer :: i

        phi_real = 0
        do i = 1, size(c)
        phi_real = phi_real + c(i) * (x_i ** (i-1))
        enddo
   end function phi_real

end program lab2
