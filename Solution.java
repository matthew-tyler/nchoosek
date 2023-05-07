import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    // This is the class you need to implement! Feel free to add members, private
    // methods etc, but don't change the public
    // method signatures.

    static class RiskLimitProcessor {
        HashMap<String, Instrument> instruments = new HashMap<>();

        public void AddLimit(String instrument, double maxValue, int maxVolume10Seconds, double maxValue1Second) {
            if (instruments.containsKey(instrument)) {
                Instrument currentInstrument = instruments.get(instrument);

                currentInstrument.setMaxValue(maxValue);
                currentInstrument.setMaxVolume10Seconds(maxVolume10Seconds);
                currentInstrument.setMaxValue1Second(maxValue1Second);
            } else {

                Instrument newInstrument = new Instrument(instrument, maxValue, maxVolume10Seconds, maxValue1Second);
                instruments.put(instrument, newInstrument);
            }

        }

        public void ProcessOrder(String instrument, long timestamp, int volume, double price) {
            if (instruments.containsKey(instrument)) {

                Order newOrder = new Order(timestamp, volume, price);

                Instrument currentInstrument = instruments.get(instrument);

                currentInstrument.addOrder(newOrder);

                String limit_reached = currentInstrument.checkOrder(newOrder);

                if (!limit_reached.isEmpty()) {
                    System.out.println(limit_reached);
                }

            }
        }

        private class Instrument {
            private String instrumentName;
            private double maxValue; // in dollars per order
            private int maxVolume10Seconds; // limit of orders in a 10s period
            private double maxValue1Second; // limit of orders in a 1s period

            private Deque<Order> oneSecondOrders;
            ArrayList<Order> orders;

            Instrument(String instrumentName, double maxValue, int maxVolume10Seconds, double maxValue1Second) {
                this.instrumentName = instrumentName;
                this.maxValue = maxValue;
                this.maxValue1Second = maxValue1Second;
                this.maxVolume10Seconds = maxVolume10Seconds;
                orders = new ArrayList<>();
                oneSecondOrders = new ArrayDeque<>();

            }

            public void setMaxValue(double maxValue) {
                this.maxValue = maxValue;
            }

            public void setMaxVolume10Seconds(int maxVolume10Seconds) {
                this.maxVolume10Seconds = maxVolume10Seconds;
            }

            public void setMaxValue1Second(double maxValue1Second) {
                this.maxValue1Second = maxValue1Second;
            }

            public void addOrder(Order order) {
                this.orders.add(order);

                this.oneSecondOrders.add(order);

                while (!oneSecondOrders.isEmpty() && (order.timestamp - oneSecondOrders.peekFirst().timestamp) > 1000) {
                    oneSecondOrders.pollFirst();
                }
            }

            public String checkOrder(Order order) {

                // Check if values are set to 0?
                // Does 0 count as no limit?
                if ((order.volume * order.price) > this.maxValue) {
                    return "MAX_VAL_LIMIT " + instrumentName;
                }
                if (!orders.isEmpty()) {
                    int currentVolume = 0;
                    double oneSecondValue = 0;

                    // Start from the most recent order
                    ListIterator<Order> iterator = orders.listIterator(orders.size());

                    while (iterator.hasPrevious()) {
                        Order existingOrder = iterator.previous();

                        // Remove orders that are older than 10 seconds
                        if ((order.timestamp - existingOrder.timestamp) > 10000) {
                            iterator.remove();
                            continue;
                        }

                        currentVolume += existingOrder.volume;

                        // Check the 10s volume limit
                        if (currentVolume > this.maxVolume10Seconds) {
                            return "MAX_VOL_10S_LIMIT " + instrumentName;
                        }

                        // Only consider orders that are within the last 1 second for the 1s value limit
                        if ((order.timestamp - existingOrder.timestamp) < 1000) {
                            oneSecondValue += (existingOrder.volume * existingOrder.price);
                        }
                    }

                    // Check the 1s value limit
                    if (oneSecondValue + (order.volume * order.price) > this.maxValue1Second) {
                        return "MAX_VAL_1S_LIMIT " + instrumentName;
                    }
                }

                return "";
            }

        }

        private class Order {
            long timestamp;
            int volume;
            double price;

            Order(long timestamp, int volume, double price) {
                this.timestamp = timestamp;
                this.volume = volume;
                this.price = price;
            }

        }
    }

    public static void main(String[] args) {
        RiskLimitProcessor store = new RiskLimitProcessor();

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String inputLine;
        try {
            while ((inputLine = reader.readLine()) != null) {
                StringTokenizer tokenizer = new StringTokenizer(inputLine);
                String action = tokenizer.nextToken();
                String instrument = tokenizer.nextToken();
                if (action.equals("LIMIT")) {
                    double maxValue = Double.parseDouble(tokenizer.nextToken());
                    int maxVolume10Seconds = Integer.parseInt(tokenizer.nextToken());
                    double maxValue1Second = Double.parseDouble(tokenizer.nextToken());
                    store.AddLimit(instrument, maxValue, maxVolume10Seconds, maxValue1Second);
                } else if (action.equals("ORDER")) {
                    long timestamp = Long.parseLong(tokenizer.nextToken());
                    int volume = Integer.parseInt(tokenizer.nextToken());
                    double price = Double.parseDouble(tokenizer.nextToken());
                    store.ProcessOrder(instrument, timestamp, volume, price);
                } else {
                    System.err.println("Malformed input!");
                    System.exit(-1);
                }
            }
        } catch (IOException e) {
            System.err.println("Input reading error!");
            System.exit(-1);
        }
    }

}