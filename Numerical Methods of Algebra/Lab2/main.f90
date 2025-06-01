program lab2
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    double precision, allocatable :: x(:), A(:,:), x_cheb(:)
    double precision, parameter :: alpha_j = 0.3_dp, PI = DACOS(-1.D0)
    double precision :: x_s, x_ss, x_sss, temp, temp1
    integer, parameter :: n = 10
    integer :: i, j

    allocate(x(n + 1))
    allocate(x_cheb(n + 1))
    allocate(A(6, 7))
    
    do i = 0, n
        x(i + 1) = alpha_j + dble(i) / dble(n)
    enddo

    x_s = x(1) + dble(2) / dble(30)
    x_ss = x(6) + dble(1) / dble(20)
    x_sss = x(11) - dble(1) / dble(30)

    ! MHK ==========================================================
    do i = 1, 6
    do j = 1, 6
        A(i,j) = phil_phik(x, i-1, j-1)
    enddo
        A(i, 7) = f_phil(x, i-1)
    enddo

    call gauss(A)

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
    print *, ' '
    deallocate(A)

    ! lagrange interpolation ==========================================
    temp = 0
    do i = 1, n
        temp = max(temp, abs(lagrangeInterpolar2(x, x(i)) - f_real(x(i))))
    enddo
    ! this line prints NaN unless you comment out line 82 (idk)
    print '(A, ES11.4)', 'overall discrep (method 2):   ', temp

    print '(A)', '3 interpolar discrep (method 1):  '
    print '(ES11.4)', lagrangeInterpolar(x, x_s) - f_real(x_s)
    print '(ES11.4)', lagrangeInterpolar(x, x_ss) - f_real(x_ss)
    print '(ES11.4)', lagrangeInterpolar(x, x_sss) - f_real(x_sss)

    print '(A)', '3 interpolar discrep (method 2):  '
    print '(ES11.4)', lagrangeInterpolar2(x, x_s) - f_real(x_s)
    print '(ES11.4)', lagrangeInterpolar2(x, x_ss) - f_real(x_ss)
    print '(ES11.4)', lagrangeInterpolar2(x, x_sss) - f_real(x_sss)
    print *, ' '

    ! lagrange cheb interpolation =====================================

    do i = 0, n
        x_cheb(i + 1) = alpha_j + dble(0.5) + cos(((2*i+1)*PI)/(2*(n+1))) / dble(2)
    enddo

    temp1 = 0
    do i = 1, n
        temp1 = max(temp1, abs(lagrangeInterpolar2(x_cheb, x(i)) - f_real(x(i))))
    enddo
    print '(A, ES11.4)', 'overall discrep (cheb):   ', temp1
    
    print '(A)', '3 interpolar discrep (cheb):  '
    print '(ES11.4)', lagrangeInterpolar2(x_cheb, x_s) - f_real(x_s)
    print '(ES11.4)', lagrangeInterpolar2(x_cheb, x_ss) - f_real(x_ss)
    print '(ES11.4)', lagrangeInterpolar2(x_cheb, x_sss) - f_real(x_sss)
    print *, ' '

    ! cubic spline ===================================================
    allocate(A(11, 12))
    
    A = dble(0)
    do i = 2, n
        A(i, i - 1) = h(x,i) / 6.D0
        A(i, i) = (h(x,i) + h(x,i+1)) / 3.D0
        A(i, i + 1) = h(x,i+1) / 6.D0
        A(i, 12) = (f_real(x(i+1)) - f_real(x(i))) / h(x,i+1) - (f_real(x(i)) - f_real(x(i-1))) / h(x,i)
    enddo
    A(1,1) = 1.D0
    A(11,11) = 1.D0

    call triagonal(A(:,:11), A(:,12))

    temp1 = 0
    do i = 1, n
        temp1 = max(temp1, abs(spline(A(:,12), x, x(i)) - f_real(x(i))))
    enddo
    print '(A, ES11.4)', 'overall discrep (spline):   ', temp1
    
    print '(A)', '3 interpolar discrep (spline):  '
    print '(ES11.4)', spline2(A(:,12), x, x_s) - f_real(x_s)
    print '(ES11.4)', spline2(A(:,12), x, x_ss) - f_real(x_ss)
    print '(ES11.4)', spline2(A(:,12), x, x_sss) - f_real(x_sss)

    deallocate(x)
    deallocate(x_cheb)
    deallocate(A)
contains

    double precision function f_real(x_i)
        implicit none
        double precision, intent(in) :: x_i
        f_real = alpha_j * EXP(-x_i) + (1_dp - alpha_j) * sin(x_i)
    end function f_real

! for MHK

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

   ! interpolar LaGrange

   double precision function lagrangeInterpolar(x, x_)
      double precision, dimension(:), intent(in) :: x
      double precision, intent(in) :: x_
      double precision :: res, temp
      integer :: i, j

      res = dble(0)
      do i = 1, size(x)
        temp = f_real(x(i))
        do j = 1, size(x)
            if (j .ne. i) then
                temp = temp * (x_ - x(j)) / (x(i) - x(j))
            endif
        enddo
        res = res + temp
      enddo

    lagrangeInterpolar = res

   end function lagrangeInterpolar

   double precision function omega(x, x_)
      double precision, dimension(:), intent(in) :: x
      double precision, intent(in) :: x_
      integer :: i

      omega = dble(1)
      do i = 1, size(x)
        omega = omega * (x_ - x(i))
      enddo

   end function omega

   double precision function omega_derivative_at(x, i)
      double precision, dimension(:), intent(in) :: x
      integer, intent(in) :: i
      double precision :: xi, res
      integer :: j
      
      xi = x(i)
      res = dble(1)
      do j = 1, size(x)
        if (j .ne. i) then
            res = res * (xi - x(j))
        endif
      enddo

      omega_derivative_at = res
   end function omega_derivative_at

   double precision function lagrangeInterpolar2(x, x_)
      double precision, dimension(:), intent(in) :: x
      double precision, intent(in) :: x_
      double precision :: res, omega_x, temp
      integer :: i
      res = dble(0)
      omega_x = omega(x, x_)
      do i = 1, size(x)
        temp = f_real(x(i)) * omega_x / ((x_ - x(i)) * omega_derivative_at(x, i))
        res = res + temp
      enddo

      lagrangeInterpolar2 = res
   end function lagrangeInterpolar2

   ! cubic spline

   double precision function h(x, i)
       double precision, dimension(:), intent(in) :: x
       integer, intent(in) :: i
       h = x(i) - x(i-1)
   end function h

    subroutine triagonal(M, f)
    real(kind=dp), dimension(:,:), intent(in) :: M
    real(kind=dp), dimension(:), intent(inout) :: f
    integer :: n, i
    real(kind=dp), dimension(size(f)) :: ksi, eta, a, b, c
    real(kind=dp) :: detI

    n = size(f)

    ! Extract tridiagonal coefficients
    do i = 2, n
        a(i - 1) = -M(i, i - 1)
    end do

    do i = 1, n - 1
        b(i) = -M(i, i + 1)
    end do

    do i = 1, n
        c(i) = M(i, i)
    end do

    ! Forward Elimination
    ksi(n) = a(n - 1) / c(n)
    eta(n) = f(n) / c(n)

    do i = n - 1, 2, -1
        detI = c(i) - ksi(i + 1) * b(i)
        ksi(i) = a(i - 1) / detI
        eta(i) = (f(i) + b(i) * eta(i + 1)) / detI
    end do

    detI = c(1) - ksi(2) * b(1)
    eta(1) = (f(1) + b(1) * eta(2)) / detI

    ! Back Substitution (storing results in f)
    f(1) = eta(1)
    do i = 1, n - 1
        f(i + 1) = ksi(i + 1) * f(i) + eta(i + 1)
    end do
    end subroutine

   double precision function spline(M, x, x_)
       double precision, dimension(:), intent(in) :: M, x
       double precision, intent(in) :: x_
       integer :: i = 2

       do while (i <= size(x) .and. x_ > x(i)) 
            i = i + 1
       end do

       spline = M(i-1) * (x(i) - x_) ** 3 / (6.D0 * h(x,i)) + &
       M(i) * (x_ - x(i-1)) ** 3 / (6.D0 * h(x,i)) + &
       (f_real(x(i-1)) - M(i) * h(x,i) ** 2 / 6.D0) * (x(i) - x_) / h(x,i) + &
       (f_real(x(i)) - M(i) * h(x,i) ** 2 / 6.D0) * (x_ - x(i-1)) / h(x,i)

   end function spline

   double precision function spline2(M, x, x_)
       double precision, dimension(:), intent(in) :: M, x
       double precision, intent(in) :: x_
       double precision :: xi_1, xi, hi, A, B
       integer :: i = 2

       do while (i <= size(x) .and. x_ > x(i)) 
            i = i + 1
       end do
       i = max(1, i)

       xi_1 = x(i-1)
       xi = x(i)
       hi = xi - xi_1

       A = (xi - x_) / hi
       B = (x_ - xi_1) / hi

       spline2 = M(i-1) * A ** 3 * hi / 6.D0 + &
           M(i) * B ** 3 * hi / 6.D0 + &
           (f_real(x(i-1)) - M(i-1) * hi * hi / 6.D0) * A + &
           (f_real(x(i)) - M(i) * hi * hi / 6.D0) * B

   end function spline2

end program lab2

!   print *, 'matrix A'
!   do i = 1, 6
!       print '(7(F10.5, 1X))', (A(i,j), j = 1, 7)
!   end do

