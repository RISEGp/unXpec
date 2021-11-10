function kde(X1, YMatrix1)
%CREATEFIGURE(X1, YMatrix1)
%  X1:  x 数据的向量
%  YMATRIX1:  y 数据的矩阵

%  由 MATLAB 于 08-Apr-2021 19:31:42 自动生成

% 创建 figure
figure1 = figure('InvertHardcopy','off','PaperUnits','inches',...
    'Color',[1 1 1]);

% 创建 axes
axes1 = axes('Parent',figure1);
hold(axes1,'on');

% 使用 plot 的矩阵输入创建多行
plot1 = plot(X1,YMatrix1,'LineWidth',1);
set(plot1(1),'DisplayName','secret = 1');
set(plot1(2),'DisplayName','secret = 0');

% 创建 ylabel
ylabel('Probability','LineWidth',1,'FontWeight','bold','FontSize',15,...
    'FontName','times new roman');

% 创建 xlabel
xlabel('Cycles','LineWidth',1,'FontWeight','bold','FontSize',15,...
    'FontName','times new roman');

% 取消以下行的注释以保留坐标区的 X 范围
% xlim(axes1,[130 250]);
% 取消以下行的注释以保留坐标区的 Y 范围
% ylim(axes1,[0 0.04]);
% 取消以下行的注释以保留坐标区的 Z 范围
% zlim(axes1,[-1 1]);
box(axes1,'on');
% 设置其余坐标区属性
set(axes1,'FontName','times new roman','FontSize',15,'FontWeight','bold',...
    'LineWidth',1,'XTick',...
    [100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250]);
% 创建 legend
legend1 = legend(axes1,'show');
set(legend1,'LineWidth',1,'FontSize',15);

