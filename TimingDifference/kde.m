function kde(X1, YMatrix1)
%CREATEFIGURE(X1, YMatrix1)
%  X1:  x ���ݵ�����
%  YMATRIX1:  y ���ݵľ���

%  �� MATLAB �� 08-Apr-2021 19:31:42 �Զ�����

% ���� figure
figure1 = figure('InvertHardcopy','off','PaperUnits','inches',...
    'Color',[1 1 1]);

% ���� axes
axes1 = axes('Parent',figure1);
hold(axes1,'on');

% ʹ�� plot �ľ������봴������
plot1 = plot(X1,YMatrix1,'LineWidth',1);
set(plot1(1),'DisplayName','secret = 1');
set(plot1(2),'DisplayName','secret = 0');

% ���� ylabel
ylabel('Probability','LineWidth',1,'FontWeight','bold','FontSize',15,...
    'FontName','times new roman');

% ���� xlabel
xlabel('Cycles','LineWidth',1,'FontWeight','bold','FontSize',15,...
    'FontName','times new roman');

% ȡ�������е�ע���Ա����������� X ��Χ
% xlim(axes1,[130 250]);
% ȡ�������е�ע���Ա����������� Y ��Χ
% ylim(axes1,[0 0.04]);
% ȡ�������е�ע���Ա����������� Z ��Χ
% zlim(axes1,[-1 1]);
box(axes1,'on');
% ������������������
set(axes1,'FontName','times new roman','FontSize',15,'FontWeight','bold',...
    'LineWidth',1,'XTick',...
    [100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250]);
% ���� legend
legend1 = legend(axes1,'show');
set(legend1,'LineWidth',1,'FontSize',15);

