%% Generates a test waveform, computes autocorrelation and analyzes it
%  

% define a sampling frequency to assume
fs = 1000;
Ts = 1/fs;

% define the function to sample
freq = 73;
omega = 2*pi*freq;
func = @(n) sin(omega*n*Ts);

% number of samples to generate, number to view
N = 100;
n = 0:1:N;
% change to view a fixed amount of lag samples
n_max = N;

% sample waveform and view it
x = func(n);
figure(1);
subplot(2,1,1);
plot(n,x);
title('Sampled Waveform');
xlabel('n')
ylabel('x[n]');

% generate autocorrelation
[Rxx, lag] = xcorr(x,x);
% extract only positive lag
Rxx = Rxx(1,(N)+(1:N));
lag = lag(1,(N)+(1:N));


% extract only the samples to view and plot
Rxx = Rxx(1,1:n_max);
lag = lag(1,1:n_max);
subplot(2,1,2);
plot(lag,Rxx);
title('Positive Lag Autocorrelation');
xlabel('\tau (samples)');
ylabel('R_{xx}(\tau)');
