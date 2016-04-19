# this code generates the last figure from the paper

source('control.r')

# WARNING: this number of nodes will eat 7GB RAM
N <- 2^14
R_coeff <- 2

Filename <- "degrees.pdf"
Cex <- 1.3

###

maxlevel <- floor( log(N, 2) )

pdf(Filename, 7, 7)

x <- 0:maxlevel

y0 <- RandomNodeDegrees(N, R_coeff, 0, maxlevel)
y1 <- RandomNodeDegrees(N, R_coeff, 0.01, maxlevel)
y5 <- RandomNodeDegrees(N, R_coeff, 0.05, maxlevel)
y10 <- RandomNodeDegrees(N, R_coeff, 0.1, maxlevel)

plot(x, y10, col = "red", pch = 25, type='b', xlab = "Level", ylab = "Average Node Degree", 
                                                    cex = Cex, cex.lab = Cex, cex.axis = Cex)
lines(x, y5, col = "orange", pch = 24, type = 'b', cex = Cex)
lines(x, y1, col = "blue",   pch = 23, type = 'b', cex = Cex)
lines(x, y0, col = "black",  pch = 1,  type = 'b', cex = Cex)

legend("topright", legend = c("0%", "1%", "5%", "10%"), pch = c(1, 23, 24, 25), 
                   col = c("black", "blue", "orange", "red"), cex = Cex)

dev.off()

cat( paste0("Written to ", Filename, '\n') )
