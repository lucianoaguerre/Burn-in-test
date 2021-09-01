void read_adc (void)
{
    float factor = 105.315;     // (2^11 bits) / {(33k/5k6) * 3.3v }
    float adc_tension = 0;
    int adc_raw = adc1_get_raw(ADC1_CHANNEL_4);
    adc_tension = (float) adc_raw / factor;  
    if (tension_entrada == 0)
    {
      tension_entrada = adc_tension;
    }
    else
    {
      tension_entrada = (tension_entrada + adc_tension) / 2;
    }
}
