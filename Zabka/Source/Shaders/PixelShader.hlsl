struct PSInput {
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

float4 main(PSInput input) : SV_TARGET{
    return float4(1, 1, 0, 1); // Bright yellow to confirm visibility
}