function [ out ] = findPeaks( Rxx )
%findPeaks Find the peaks of an autocorrelation signal
%   Detailed explanation goes here

indices= [];

% get the magnitude of each lag position
absr = abs(Rxx);
N = length(absr);

max = -1;
maxIndex = -1;

for n = N:-1:1
    current = absr(n);
    
    % if we've gone below the last maximum
    if current < max
        % if the last position was a max
        if n == maxIndex-1
            % last index was a peak
            indices = [maxIndex indices]; 
        end
    else
        % update the latest maximum value
        %if current >= max
            max = current;
            maxIndex = n;    
        %end
    end
    
    out = indices;
end

