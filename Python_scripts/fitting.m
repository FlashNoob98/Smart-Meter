close all; clear;clc;
% Carica il file
load('dati_cal.mat');

% Estrai i dati come array
V = table2array(tensioni);   % dimensione: Nx13
I = table2array(correnti);   % dimensione: Nx12


% Valori reali noti
valori_reali_tensione = (0:20:240);  % Da 240 a 0 passo 20 V
valori_reali_corrente = (0:11); % da 0 a 11 passo 1 A


% Numero di acquisizioni
num_tensioni = size(V,2);
num_correnti = size(I,2);

% Prealloca vettori per RMS calcolati
v_rms_adc = zeros(1, num_tensioni);
i_rms_adc = zeros(1, num_correnti);

% --- Calcolo RMS TENSIONI ---
for k = 1:num_tensioni
    seg = V(:,k)/0.413560;
    seg = seg - mean(seg);           % Rimuovi offset
    v_rms_adc(k) = rms(seg);         % Calcola RMS centrato
end

% --- Calcolo RMS CORRENTI ---
for k = 1:num_correnti
    seg = I(:,k);
    seg = seg - mean(seg);           % Rimuovi offset
    i_rms_adc(k) = rms(seg);         % Calcola RMS centrato
end

% --- Regressione lineare: TENSIONE ---
coeff_t = polyfit(v_rms_adc,valori_reali_tensione, 1);
G_v = coeff_t(1);
O_v = coeff_t(2);

% --- Regressione lineare: CORRENTE ---
coeff_i = polyfit(i_rms_adc, valori_reali_corrente, 1);
G_i = coeff_i(1);
O_i = coeff_i(2);

% --- Risultati ---
fprintf('\n--- Calibrazione TENSIONE ---\n');
fprintf('Guadagno G = %.6f\n', G_v);
fprintf('Offset   O = %.6f\n', O_v);

fprintf('\n--- Calibrazione CORRENTE ---\n');
fprintf('Guadagno G = %.6f\n', G_i);
fprintf('Offset   O = %.6f\n', O_i);

% --- Grafici di calibrazione ---
figure;
subplot(2,1,1);
plot(v_rms_adc, valori_reali_tensione, 'bo', 'DisplayName', 'Dati');
hold on;
fplot(@(x) G_v*x + O_v, [min(v_rms_adc), max(v_rms_adc)], 'r', 'DisplayName', 'Fit lineare');
title('Calibrazione Tensione');
xlabel('ADC RMS'); ylabel('Valore Reale [V]');
legend; grid on;

subplot(2,1,2);
plot(i_rms_adc, valori_reali_corrente, 'bo', 'DisplayName', 'Dati');
hold on;
fplot(@(x) G_i*x + O_i, [min(i_rms_adc), max(i_rms_adc)], 'r', 'DisplayName', 'Fit lineare');
title('Calibrazione Corrente');
xlabel('ADC RMS'); ylabel('Valore Reale [A]');
legend; grid on;
